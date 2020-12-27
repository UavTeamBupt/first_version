//
// Author: Emin Ilker Cetinbas (niw3_at_yahoo_d0t_com)
// Generalization: Andras Varga
// Copyright (C) 2005 Emin Ilker Cetinbas, Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/common/INETMath.h"
#include "inet/mobility/single/MassMobility.h"
#include<iostream>
using namespace std;

namespace inet {

Define_Module(MassMobility);

MassMobility::MassMobility()
{
}

void MassMobility::initialize(int stage)
{
    LineSegmentsMobilityBase::initialize(stage);

    EV_TRACE << "initializing MassMobility stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        //通过这种方式与ned文件关联 获取 deg是真正转为类型值 而par是一个获取
        rad heading = deg(par("initialMovementHeading"));
        rad elevation = deg(par("initialMovementElevation"));
        changeIntervalParameter = &par("changeInterval");
        angleDeltaParameter = &par("angleDelta");
        rotationAxisAngleParameter = &par("rotationAxisAngle");
        speedParameter = &par("speed");
        quaternion = Quaternion(EulerAngles(heading, -elevation, rad(0)));
        WATCH(quaternion);
    }
}

void MassMobility::orient()
{
    if (faceForward)
        lastOrientation = quaternion;
}

void MassMobility::setTargetPosition()
{
    //rad代表弧度 即 radian
    rad angleDelta = deg(angleDeltaParameter->doubleValue());//沿旋转轴的旋转速度矢量变化
    rad rotationAxisAngle = deg(rotationAxisAngleParameter->doubleValue());//旋转轴
    Quaternion dQ = Quaternion(Coord::X_AXIS, rotationAxisAngle.get()) * Quaternion(Coord::Z_AXIS, angleDelta.get());
    quaternion = quaternion * dQ;
    quaternion.normalize();//单位化这个矢量(使其长为1 这样每秒就沿着这个方向走一个规定的长度)
    Coord direction = quaternion.rotate(Coord::X_AXIS);//真正转化为方向向量 从Quaternion转为Coord
    simtime_t nextChangeInterval = *changeIntervalParameter;//更新的周期
    EV_DEBUG << "interval: " << nextChangeInterval << endl;
    sourcePosition = lastPosition;//源位置
    targetPosition = lastPosition + direction * (*speedParameter) * nextChangeInterval.dbl();//目标位置
    previousChange = simTime();
    nextChange = previousChange + nextChangeInterval;//下次变化的时刻=当前仿真时间+变化周期
}

void MassMobility::move()
{
    simtime_t now = simTime();//当前的仿真时间
    rad dummyAngle;
    if (now == nextChange) {//当前时间到达了需要变化的时刻
        lastPosition = targetPosition;//更新上一个位置为目标位置(即已经到达了目标位置)
        handleIfOutside(REFLECT, targetPosition, lastVelocity, dummyAngle, dummyAngle, quaternion);//走到边界 进行反弹(注意用的速度上次算出来)
        EV_INFO << "reached current target position = " << lastPosition << endl;
        // cout<<"!!!!!!!!!!!!!!!!!!!!!!lastPosition:("<<lastPosition.getX()<<","<<lastPosition.getY()<<","<<lastPosition.getZ()<<")"<<endl;
        // EV_INFO <<"!!!!!!!!!!!!!!!!!!lastPosition:("<<lastPosition.getX()<<","<<lastPosition.getY()<<","<<lastPosition.getZ()<<")"<<endl;
        setTargetPosition();//设定下次节点往哪走(但还没走 等待下一个变化周期到来)
        EV_INFO << "new target position = " << targetPosition << ", next change = " << nextChange << endl;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();//我下次移动过程中的速度矢量
        handleIfOutside(REFLECT, targetPosition, lastVelocity, dummyAngle, dummyAngle, quaternion);
    }
    else if (now > lastUpdate) {//当前时刻 > 上一次更新移动状态时的仿真时间(基本都是)
        //若ASSERT里面的表达式为false 则会报异常
        ASSERT(nextChange == -1 || now < nextChange);//没有下次变化了 或者 当前时刻还没有到下次变化的时刻(基本都是)
        double alpha = (now - previousChange) / (nextChange - previousChange);//距离下次时刻变化已经发生了百分之多少
        lastPosition = sourcePosition * (1 - alpha) + targetPosition * alpha;//按比例进行节点位置的变化
        handleIfOutside(REFLECT, targetPosition, lastVelocity, dummyAngle, dummyAngle, quaternion);
    }
}

double MassMobility::getMaxSpeed() const
{
    return speedParameter->isExpression() ? NaN : speedParameter->doubleValue();
}

} // namespace inet

