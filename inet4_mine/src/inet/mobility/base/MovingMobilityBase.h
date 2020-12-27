/* -*- mode:c++ -*- ********************************************************
 * file:        MovingMobilityBase.h
 *
 * author:      Daniel Willkomm, Andras Varga
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              (C) 2005 Andras Varga
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

#ifndef __INET_MOVINGMOBILITYBASE_H
#define __INET_MOVINGMOBILITYBASE_H

#include "inet/mobility/base/MobilityBase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <omnetpp.h>
#include <string>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "json/json.h"

using namespace omnetpp;
using namespace std;

namespace inet {

/**
 * @brief Base class for moving mobility modules. Periodically emits a signal with the current mobility state.
 *
 * @ingroup mobility
 * @author Levente Meszaros
 */
class INET_API MovingMobilityBase : public MobilityBase
{
  protected:
    /** @brief The message used for mobility state changes. */
    cMessage *moveTimer;

    /** @brief The simulation time interval used to regularly signal mobility state changes.
     *
     * The 0 value turns off the signal. */
    simtime_t updateInterval;

    /** @brief A mobility model may decide to become stationary at any time.
     *
     * The true value disables sending self messages. */
    bool stationary;

    /** @brief The last velocity that was reported at lastUpdate. */
    Coord lastVelocity;

    /** @brief The last angular velocity that was reported at lastUpdate. */
    Quaternion lastAngularVelocity;

    /** @brief The simulation time when the mobility state was last updated. */
    simtime_t lastUpdate;

    /** @brief The next simulation time when the mobility module needs to update its internal state.
     *
     * The -1 value turns off sending a self message for the next mobility state change. */
    simtime_t nextChange;

    bool faceForward;

    //TODO new add 属性
    bool getOthersPosition;
    std::map<std::string,Coord> basicNodePositionMap;
    std::map<std::string,Coord> routerNodePositionMap;
    int basicNodeNum;
    int routerNodeNum;
    simtime_t getAllNodeStatusInterval;
    simtime_t nextGetAllNodeStatusTime;
    const char* basicNodeFile = "./basicNodePosition.json";
    const char* routerNodeFile = "./routerNodePosition.json";
    // Json::Value testroot;//Json正文部分，用于组装
    // Json::StyledWriter jsonwriter;//用于写入Json文件
    // std::ofstream jsonos;
  protected:
    MovingMobilityBase();

    virtual ~MovingMobilityBase();

    virtual void initialize(int stage) override;

    virtual void initializePosition() override;

    virtual void handleSelfMessage(cMessage *message) override;

    /** @brief Schedules the move timer that will update the mobility state. */
    void scheduleUpdate();

    /** @brief Moves and notifies listeners. */
    void moveAndUpdate();

    /** @brief Moves according to the mobility model to the current simulation time.
     *
     * Subclasses must override and update lastPosition, lastVelocity, lastUpdate, nextChange
     * and other state according to the mobility model.
     */
    virtual void move() = 0;

    virtual void orient();

    //TODO new add 方法
    void updateOtherNodesPosition();
    void printOtherNodesPosition();
    void setBasicNodeCluster();
    int file_exist(const char* file_path);

  public:
    virtual Coord getCurrentPosition() override;
    virtual Coord getCurrentVelocity() override;
    virtual Coord getCurrentAcceleration() override { throw cRuntimeError("Invalid operation"); }

    virtual Quaternion getCurrentAngularPosition() override;
    virtual Quaternion getCurrentAngularVelocity() override;
    virtual Quaternion getCurrentAngularAcceleration() override { throw cRuntimeError("Invalid operation"); }
};

} // namespace inet

#endif // ifndef __INET_MOVINGMOBILITYBASE_H

