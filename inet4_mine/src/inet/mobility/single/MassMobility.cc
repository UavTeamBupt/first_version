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
        //ͨ�����ַ�ʽ��ned�ļ����� ��ȡ deg������תΪ����ֵ ��par��һ����ȡ
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
    //rad������ �� radian
    rad angleDelta = deg(angleDeltaParameter->doubleValue());//����ת�����ת�ٶ�ʸ���仯
    rad rotationAxisAngle = deg(rotationAxisAngleParameter->doubleValue());//��ת��
    Quaternion dQ = Quaternion(Coord::X_AXIS, rotationAxisAngle.get()) * Quaternion(Coord::Z_AXIS, angleDelta.get());
    quaternion = quaternion * dQ;
    quaternion.normalize();//��λ�����ʸ��(ʹ�䳤Ϊ1 ����ÿ����������������һ���涨�ĳ���)
    Coord direction = quaternion.rotate(Coord::X_AXIS);//����ת��Ϊ�������� ��QuaternionתΪCoord
    simtime_t nextChangeInterval = *changeIntervalParameter;//���µ�����
    EV_DEBUG << "interval: " << nextChangeInterval << endl;
    sourcePosition = lastPosition;//Դλ��
    targetPosition = lastPosition + direction * (*speedParameter) * nextChangeInterval.dbl();//Ŀ��λ��
    previousChange = simTime();
    nextChange = previousChange + nextChangeInterval;//�´α仯��ʱ��=��ǰ����ʱ��+�仯����
}

void MassMobility::move()
{
    simtime_t now = simTime();//��ǰ�ķ���ʱ��
    rad dummyAngle;
    if (now == nextChange) {//��ǰʱ�䵽������Ҫ�仯��ʱ��
        lastPosition = targetPosition;//������һ��λ��ΪĿ��λ��(���Ѿ�������Ŀ��λ��)
        handleIfOutside(REFLECT, targetPosition, lastVelocity, dummyAngle, dummyAngle, quaternion);//�ߵ��߽� ���з���(ע���õ��ٶ��ϴ������)
        EV_INFO << "reached current target position = " << lastPosition << endl;
        // cout<<"!!!!!!!!!!!!!!!!!!!!!!lastPosition:("<<lastPosition.getX()<<","<<lastPosition.getY()<<","<<lastPosition.getZ()<<")"<<endl;
        // EV_INFO <<"!!!!!!!!!!!!!!!!!!lastPosition:("<<lastPosition.getX()<<","<<lastPosition.getY()<<","<<lastPosition.getZ()<<")"<<endl;
        setTargetPosition();//�趨�´νڵ�������(����û�� �ȴ���һ���仯���ڵ���)
        EV_INFO << "new target position = " << targetPosition << ", next change = " << nextChange << endl;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();//���´��ƶ������е��ٶ�ʸ��
        handleIfOutside(REFLECT, targetPosition, lastVelocity, dummyAngle, dummyAngle, quaternion);
    }
    else if (now > lastUpdate) {//��ǰʱ�� > ��һ�θ����ƶ�״̬ʱ�ķ���ʱ��(��������)
        //��ASSERT����ı��ʽΪfalse ��ᱨ�쳣
        ASSERT(nextChange == -1 || now < nextChange);//û���´α仯�� ���� ��ǰʱ�̻�û�е��´α仯��ʱ��(��������)
        double alpha = (now - previousChange) / (nextChange - previousChange);//�����´�ʱ�̱仯�Ѿ������˰ٷ�֮����
        lastPosition = sourcePosition * (1 - alpha) + targetPosition * alpha;//���������нڵ�λ�õı仯
        handleIfOutside(REFLECT, targetPosition, lastVelocity, dummyAngle, dummyAngle, quaternion);
    }
}

double MassMobility::getMaxSpeed() const
{
    return speedParameter->isExpression() ? NaN : speedParameter->doubleValue();
}

} // namespace inet

