#ifndef SIMDRIVER_H
#define SIMDRIVER_H

#include "base_definitions.h"
#include "event.h"
#include "spaceentity.h"
#include "timedriver.h"

enum PlayerType{
    ENEMY,
    NEUTR,
    ALLY
};

// Controllable user.
class Player
{
public:
    Player();

    size_t id;
    PlayerType type;
    std::map<size_t, VehicleEntity> vehicles;

    static size_t count;

};

// Not controllable. It is mother nature.
class Nature
{
public:
    std::map<size_t, CelestialBody> celestialBodies;
    std::map<size_t, StrayEntity> strayEntities;
};

class TimePoint
{
public:
    TimePoint(const Event &e);

    // Adjust an existing time point.
    void adjust(const Event &e);
    void filterTimeStep();

    msecs timePoint;
    msecs maxTimeStep;
    int requestBalance = 0;

    static std::map<size_t, msecs> timeSteps;
    static int requestTotal;
};

// Manages simulation, players, nature, time and their properties.
class SimDriver
{
public:
    SimDriver();

    void run();
    void stop();

    // Compile events into time points to execute.
    void compile();

    void registerEvent(const Event &e);

    Nature nature;
    std::map<size_t, Player> players;
    TimeDriver time;

    // It will sort itself automatically and there will be not a duplicate member.
    // I am lazy and can't really bother with this rn.
    std::map<msecs, TimePoint> timePoints;

};

#endif // SIMDRIVER_H
