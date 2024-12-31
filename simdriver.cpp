#include "simdriver.h"

int TimePoint::requestTotal = 0;

Player::Player(){}

SimDriver::SimDriver() {}

void SimDriver::run()
{

}

void SimDriver::stop()
{

}

void SimDriver::compile()
{
    timePoints.clear();

    // Register events from celestial bodies.
    for(const auto &cbItr : nature.celestialBodies){
        for(const auto &eItr : cbItr.second.events){
            registerEvent(eItr.second);
        }
    }

    // Register events from stray entities.
    for(const auto &seItr : nature.strayEntities){
        for(const auto &eItr : seItr.second.events){
            registerEvent(eItr.second);
        }
    }

    // Register events from vehicles.
    for(const auto &playerItr : players){
        for(const auto &vItr : playerItr.second.vehicles){
            for(const auto &eItr : vItr.second.events){
                registerEvent(eItr.second);
            }
        }
    }

    // Re-arrange request balances.
    for(auto &tpItr: timePoints){
        TimePoint::requestTotal += tpItr.second.requestBalance;
        tpItr.second.requestBalance = TimePoint::requestTotal;
    }

    TimePoint::timeSteps.clear();
}

void SimDriver::registerEvent(const Event &e)
{
    auto tpItr = timePoints.find(e.tAbsolute);
    if(tpItr == timePoints.end()){
        timePoints.insert({e.tAbsolute, TimePoint(e)});
    }else{
        tpItr->second.adjust(e);
    }
}


TimePoint::TimePoint(const Event &e)
{
    timePoint = e.tAbsolute;
    maxTimeStep = e.timeStep;

    if(e.request == TimeStepRequest::DEFAULT){
        requestBalance--;
        timeSteps.erase(e.id_pair);
    }
    else if(e.request == TimeStepRequest::CHANGE){
        requestBalance++;
        timeSteps.insert({e.id, e.timeStep});
    }
    else if(e.request == TimeStepRequest::NO_PREF){

    }

    filterTimeStep();
}

void TimePoint::adjust(const Event &e)
{
    if(e.timeStep < maxTimeStep){
        maxTimeStep = e.timeStep;
    }

    if(e.request == TimeStepRequest::DEFAULT){
        requestBalance--;
    }
    else if(e.request == TimeStepRequest::CHANGE){
        requestBalance++;
    }
    else if(e.request == TimeStepRequest::NO_PREF){

    }

    filterTimeStep();
}

void TimePoint::filterTimeStep()
{
    for(const auto &ts : timeSteps){
        if(maxTimeStep > ts.second){
            maxTimeStep = ts.second;
        }
    }
}
