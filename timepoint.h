#ifndef TIMEPOINT_H
#define TIMEPOINT_H

#include <map>

#include "event.h"

// Compiled TimePoint object for simulation. Contains data about how simulation will work.
class TimePoint
{
public:
    template<class T>
    TimePoint(const T &e)
    {
        maxTimeStep = e.timeStep;

        if(e.request == TimeStepRequest::REVERT){
            requestBalance--;
            tempTimeSteps.erase(e.id_pair);
        }
        else if(e.request == TimeStepRequest::CHANGE){
            requestBalance++;
            tempTimeSteps.insert({e.id, e.timeStep});
        }
        else if(e.request == TimeStepRequest::NO_PREF){

        }

        filterTimeStep();
    }

    // Adjust an existing time point.
    template<class T>
    void adjust(const T &e)
    {
        if(e.timeStep < maxTimeStep){
            maxTimeStep = e.timeStep;
        }

        if(e.request == TimeStepRequest::REVERT){
            requestBalance--;
        }
        else if(e.request == TimeStepRequest::CHANGE){
            requestBalance++;
        }
        else if(e.request == TimeStepRequest::NO_PREF){

        }

        filterTimeStep();
    }

    // Sets maxTimeStep to the lowest timeStep value that is requested from simulation.
    void filterTimeStep();

    msecs timeLength;
    msecs maxTimeStep;

    // = 0 : Default time step,
    // > 0 : Variable time step.
    int requestBalance = 0;

    // Temporary timeSteps by event ids to calculate minimum timeStep.
    static std::map<size_t, msecs> tempTimeSteps;
    // Auxiliary total request counter to calculate real requestBalance.
    static int requestTotal;
};

#endif // TIMEPOINT_H
