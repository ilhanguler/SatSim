#include "timedriver.h"

TimeDriver::TimeDriver(QObject *parent)
    : QObject{parent}
{}

TimeDriver::TimeDriver(QDateTime simTime, qint64 deltaMSecs)
{
    this->simTime = simTime;
    this->deltaMSecs = deltaMSecs;
    timer.start();
}

void TimeDriver::passDeltaTime()
{
    simTime = simTime.addMSecs(deltaMSecs);
    emit timePassed();
}
