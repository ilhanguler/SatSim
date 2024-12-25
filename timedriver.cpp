#include "timedriver.h"


TimeDriver::TimeDriver(QObject *parent)
    : QObject{parent}
{

}

TimeDriver::TimeDriver(QDateTime simTime, unsigned long long deltaMSecs)
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

void TimeDriver::waitSimulation(){
    passDeltaTime();
}

void TimeDriver::updateSystemTime(){
    systemTime = QDateTime::currentDateTime();
}
