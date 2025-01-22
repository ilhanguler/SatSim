#include "simdriver.h"

// ===== SimDriver ===== This section belongs to SimDriver.

SimDriver::SimDriver() {}

void SimDriver::run()
{
    for(const auto &tp : timePoints){

        prepareSimCore(tp.second);

        // Stray entities simulation
        for(auto &se : enviroment.strayEntities){
            auto range = se.collisions.equal_range(tp.first);
            for(auto cItr = range.first; cItr != range.second; ++cItr){

            }
        }

        // Vehicles simulation
        for(auto &player : players){
            for(auto &v : player.second.vehicles){
                auto range = v.collisions.equal_range(tp.first);
                for(auto cItr = range.first; cItr != range.second; ++cItr){

                }
                auto range2 = v.thrusters.equal_range(tp.first);
                for(auto tItr = range2.first; tItr != range2.second; ++tItr){

                }
            }
        }

        // Celestial bodies simulation
        for(auto &cb : enviroment.celestialBodies){
            auto range = cb.collisions.equal_range(tp.first);
            for(auto cItr = range.first; cItr != range.second; ++cItr){

            }
        }

        simCore.sgpTaylorSingleCore(enviroment.celestialBodies, players, enviroment.strayEntities, simCore.deltaMSecs, simCore.simLengthByMsecs);

    }
}

void SimDriver::prepareSimCore(const TimePoint &tp){

    // Adjust deltaMSecs and update properties of simCore according to compiled timePoints
    if(tp.requestBalance > 0){
        simCore.deltaMSecs = tp.maxTimeStep;
    }
    else{
        simCore.deltaMSecs = simCore.deltaMSecsDefault;
    }

    simCore.simLengthByMsecs = tp.timeLength;
    simCore.initDTs(simCore.deltaMSecs);
}

void SimDriver::compile()
{
    timePoints.clear();

    // Register events from celestial bodies.
    for(const auto &cb : enviroment.celestialBodies){
        for(const auto &c : cb.collisions){
            registerEvent(c.second);
        }
    }

    // Register events from stray entities.
    for(const auto &se : enviroment.strayEntities){
        for(const auto &c : se.collisions){
            registerEvent(c.second);
        }
    }

    // Register events from vehicles.
    for(const auto &player : players){
        for(const auto &v : player.second.vehicles){
            for(const auto &c : v.collisions){
                registerEvent(c.second);
            }
            for(const auto &t : v.thrusters){
                registerEvent(t.second);
            }
        }
    }

    // Re-arrange request balances.
    for(auto &tp: timePoints){
        TimePoint::requestTotal += tp.second.requestBalance;
        tp.second.requestBalance = TimePoint::requestTotal;
    }

    // Calculate timeLengths of timePoints.
    msecs prevTimePoint = 0;
    for(auto tpItr = timePoints.begin(); tpItr != timePoints.end(); tpItr++){
        tpItr->second.timeLength = tpItr->first - prevTimePoint;
        prevTimePoint = tpItr ->first;
    }

    TimePoint::tempTimeSteps.clear();
}

void SimDriver::initialize(CelestialBody &&celestialBody)
{
    enviroment.celestialBodies.push_back(celestialBody);
}

void SimDriver::initialize(StrayEntity &&strayEntity)
{
    enviroment.strayEntities.push_back(strayEntity);
}

void SimDriver::initialize(size_t playerID, VehicleEntity &&vehicle)
{
    auto pItr = players.find(playerID);
    if(pItr != players.end()){
        pItr->second.vehicles.push_back(vehicle);
    }
}

void SimDriver::initialize(Player &&player)
{
    players.insert({player.id, player});
}

