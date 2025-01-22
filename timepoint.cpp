#include "timepoint.h"

// Static TimePoint members

int TimePoint::requestTotal = 0;
std::map<size_t, msecs> TimePoint::tempTimeSteps;



void TimePoint::filterTimeStep()
{
    for(const auto &ts : tempTimeSteps){
        if(maxTimeStep > ts.second){
            maxTimeStep = ts.second;
        }
    }
}
