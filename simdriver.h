#ifndef SIMDRIVER_H
#define SIMDRIVER_H

#include "base_definitions.h"
#include "spaceentity.h"
#include "timepoint.h"
#include "simcore.h"
#include "player.h"

// Manages simulation, players, nature, time and their properties.
class SimDriver
{
public:
    SimDriver();

    // Run simulation after compilation finished.
    // compile -> run
    void run();

    // Compile events into time points to execute.
    // compile -> run
    void compile();

    // Prepare simCore properties before running the simulation.
    // This function has to be called for each TimePoints.
    void prepareSimCore(const TimePoint &tp);

    void initialize(CelestialBody &&celestialBody);

    void initialize(StrayEntity &&strayEntity);

    void initialize(size_t playerID, VehicleEntity &&vehicle);

    void initialize(Player &&player);

    template<class T>
    void registerEvent(const T &e)
    {
        auto tpItr = timePoints.find(e.timeMSecs);

        if(tpItr == timePoints.end()){
            timePoints.insert({e.timeMSecs, TimePoint(e)});
        }else{
            tpItr->second.adjust(e);
        }
    }

    SimCore simCore;
    Enviroment enviroment;
    std::map<size_t, Player> players;

    // It will sort itself automatically and there will be not a duplicate member.
    std::map<msecs, TimePoint> timePoints;
};

#endif // SIMDRIVER_H
