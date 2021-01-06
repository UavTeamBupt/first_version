/* -*- mode:c++ -*- ********************************************************
 * file:        MovingMobilityBase.cc
 *
 * author:      Daniel Willkomm, Andras Varga, Zoltan Bojthe
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              (C) 2005 Andras Varga
 *              (C) 2011 Zoltan Bojthe
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 **************************************************************************/

#include "inet/mobility/base/MovingMobilityBase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omnetpp.h>
#include "json/json.h"


using namespace omnetpp;
using namespace std;

namespace inet {

MovingMobilityBase::MovingMobilityBase() :
    moveTimer(nullptr),
    updateInterval(0),
    stationary(false),
    lastVelocity(Coord::ZERO),
    lastUpdate(0),
    nextChange(-1),
    faceForward(false),
    //TODO new add
    getOthersPosition(false),
    basicNodeNum(0),
    routerNodeNum(0),
    getAllNodeStatusInterval(5),
    nextGetAllNodeStatusTime(-1),
    networkName("UAVNetwork_Multi")
{
}

MovingMobilityBase::~MovingMobilityBase()
{
    cancelAndDelete(moveTimer);
}


//检查文件是否存在
int MovingMobilityBase::file_exist(const char* file_path){
    if(access(file_path,F_OK)==0){//文集存在
        return 0;
    }
    return -1;
}

void MovingMobilityBase::initialize(int stage)
{
    MobilityBase::initialize(stage);
    EV_TRACE << "initializing MovingMobilityBase stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        moveTimer = new cMessage("move");
        updateInterval = par("updateInterval");
        faceForward = par("faceForward");
        //TODO new add
        getOthersPosition = par("getOthersPosition");
        basicNodeNum = par("basicNodeNum");
        routerNodeNum = par ("routerNodeNum");
        getAllNodeStatusInterval = par("getAllNodeStatusInterval");
        networkName= par("networkName");
    }
    //TODO new add
    if (getOthersPosition==true){
        usleep(5000);//当找到目标簇头的时候，希望通过暂停5ms以使其他节点都加载完基础位置信息.
        updateOtherNodesPosition();
//        printOtherNodesPosition();
    }
}

void MovingMobilityBase::initializePosition()
{
    MobilityBase::initializePosition();
    lastUpdate = simTime();
    //TODO new add
    nextGetAllNodeStatusTime = simTime();
    
    scheduleUpdate();
}

void MovingMobilityBase::updateOtherNodesPosition()
{
    //普通node的map
    for(int i =0;i<basicNodeNum;i++)
    {
        //注意当前的inet仅仅适用于我现在这个工程了!
//        std::string nodePathName = std::string("UAVNetwork_Multi.basicHosts[")+std::to_string(i)+std::string("].mobility");
        std::string nodePathName = networkName+std::string(".basicHosts[")+std::to_string(i)+std::string("].mobility");
        cModule* nodeModule = this->getModuleByPath(nodePathName.c_str());
//        cout<<"is the nodeModule nullptr?"<<nodeModule<<endl;
        //MassMobility*转化为MovingMobilityBase(也就是本类)
        MovingMobilityBase* MMB= check_and_cast<MovingMobilityBase*>(nodeModule);
        //basicHosts[i]和它对应的位置(Coord类)
        basicNodePositionMap[std::string("basicHosts[")+std::to_string(i)+std::string("]")]=MMB->getCurrentPosition();
    }
    //簇头node的map
    for(int i =0;i<routerNodeNum;i++)
    {
//        std::string nodePathName = std::string("UAVNetwork_Multi.hostRouters[")+std::to_string(i)+std::string("].mobility");
        std::string nodePathName = networkName+std::string(".hostRouters[")+std::to_string(i)+std::string("].mobility");
        cModule* nodeModule = this->getModuleByPath(nodePathName.c_str());
        MovingMobilityBase* MMB= check_and_cast<MovingMobilityBase*>(nodeModule);
        routerNodePositionMap[std::string("hostRouters[")+std::to_string(i)+std::string("]")]=MMB->getCurrentPosition();
    }

    //普通节点写入json文件
    Json::Value root;
    for(std::map<std::string,Coord>::iterator i = basicNodePositionMap.begin();i != basicNodePositionMap.end();i++){
        Json::Value partner;
        partner[i->first].append((i->second).getX());
        partner[i->first].append((i->second).getY());
        partner[i->first].append((i->second).getZ());
        root["basicNodePosition"].append(partner);
    }
    //生成json
    Json::StyledWriter sw;
    std::ofstream os;
    os.open(basicNodeFile);
    os<<sw.write(root);
    os.close();


    //簇头节点写入json文件
    Json::Value root_2;
    for(std::map<std::string,Coord>::iterator i = routerNodePositionMap.begin();i != routerNodePositionMap.end();i++){
        Json::Value partner;
        partner[i->first].append((i->second).getX());
        partner[i->first].append((i->second).getY());
        partner[i->first].append((i->second).getZ());
        root_2["routerNodePosition"].append(partner);
    }
    //生成json
    Json::StyledWriter sw_2;
    std::ofstream os_2;
    os_2.open(routerNodeFile);
    os_2<<sw_2.write(root_2);
    os_2.close();

}

void MovingMobilityBase::setBasicNodeCluster()
{
    const char* to_search_file="./clusterResult.json";
    while(true)
    {
        long handle = file_exist(to_search_file);
        if (handle==-1)
        {
            continue;
        }
        //找到了待写入的文件 解析
        Json::Reader reader;
        Json::Value root;
        std::ifstream in(std::string(to_search_file), std::ios::binary);
        if (reader.parse(in, root)){//将来自Jsonpath(实际就是Action.json或Action_base.json)的字符串解析到root中
            //遍历 所有交换机
            for(std::map<std::string,Coord>::iterator i = basicNodePositionMap.begin();i != basicNodePositionMap.end();i++){
                //只搞basicHosts的
//                std::string nodePathName = std::string("UAVNetwork_Multi.")+std::string(i->first)+std::string(".mobility");
                std::string nodePathName = networkName+std::string(".")+std::string(i->first)+std::string(".mobility");
                cModule* nodeModule = this->getModuleByPath(nodePathName.c_str());
                MobilityBase* MB= check_and_cast<MobilityBase*>(nodeModule);
                MB->setClusterHead(root[i->first].asString());//把第i个node对应的簇头设置进去(即root[i->first])
            }
        }               
        break;
    }
}

void MovingMobilityBase::printOtherNodesPosition()
{
    for(std::map<std::string,Coord>::iterator i = basicNodePositionMap.begin();i != basicNodePositionMap.end();i++){
        string nowNode=i->first;
        cout<<"basicNode:"<<nowNode<<endl;
        cout<<"position:("<<(i->second).getX()<<","<<(i->second).getY()<<","<<(i->second).getZ()<<")"<<endl;
    }
    for(std::map<std::string,Coord>::iterator i = routerNodePositionMap.begin();i != routerNodePositionMap.end();i++){
        string nowNode=i->first;
        cout<<"routerNode:"<<nowNode<<endl;
        cout<<"position:("<<(i->second).getX()<<","<<(i->second).getY()<<","<<(i->second).getZ()<<")"<<endl;
    }
    cout<<"==========================================================================="<<endl;
}

void MovingMobilityBase::moveAndUpdate()
{
    simtime_t now = simTime();
    if (nextChange == now || lastUpdate != now) {
        move();
        orient();
        lastUpdate = simTime();
        emitMobilityStateChangedSignal();
    }
}

void MovingMobilityBase::orient()
{
    if (faceForward) {
        // determine orientation based on direction
        if (lastVelocity != Coord::ZERO) {
            Coord direction = lastVelocity;
            direction.normalize();
            auto alpha = rad(atan2(direction.y, direction.x));
            auto beta = rad(-asin(direction.z));
            auto gamma = rad(0.0);
            lastOrientation = Quaternion(EulerAngles(alpha, beta, gamma));
        }
    }
}

void MovingMobilityBase::handleSelfMessage(cMessage *message)
{
    moveAndUpdate();
    scheduleUpdate();
    //TODO new add
    if (getOthersPosition==true){//目标簇头的日常更新 注意这个时候暂时设置更新周期为每2s变化一次
        if(nextGetAllNodeStatusTime<simTime())
        {
            updateOtherNodesPosition();
//            printOtherNodesPosition();
            setBasicNodeCluster();
            nextGetAllNodeStatusTime=simTime()+getAllNodeStatusInterval;
        }
    }
}

void MovingMobilityBase::scheduleUpdate()
{
    cancelEvent(moveTimer);
    if (!stationary && updateInterval != 0) {
        // periodic update is needed
        simtime_t nextUpdate = simTime() + updateInterval;
        if (nextChange != -1 && nextChange < nextUpdate)
            // next change happens earlier than next update
            scheduleAt(nextChange, moveTimer);
        else
            // next update happens earlier than next change or there is no change at all
            scheduleAt(nextUpdate, moveTimer);
    }
    else if (nextChange != -1)
        // no periodic update is needed
        scheduleAt(nextChange, moveTimer);
}

Coord MovingMobilityBase::getCurrentPosition()
{
    moveAndUpdate();
    return lastPosition;
}

Coord MovingMobilityBase::getCurrentVelocity()
{
    moveAndUpdate();
    return lastVelocity;
}

Quaternion MovingMobilityBase::getCurrentAngularPosition()
{
    moveAndUpdate();
    return lastOrientation;
}

Quaternion MovingMobilityBase::getCurrentAngularVelocity()
{
    moveAndUpdate();
    return lastAngularVelocity;
}

} // namespace inet

