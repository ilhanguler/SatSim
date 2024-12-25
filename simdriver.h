#ifndef SIMDRIVER_H
#define SIMDRIVER_H

#include "spaceentity.h"

class Player
{
public:
    Player();
    int id;
    int type;
    std::vector<VehicleEntity> vehicles;

};

class SimDriver
{
public:
    SimDriver();

    std::vector<CelestialBody> celestialBodies;
    std::vector<StrayEntity> strayEntities;
    std::vector<Player> players;

    void run();
    void stop();
    void compile();

};

#endif // SIMDRIVER_H
