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

};

// Not controllable. It is mother nature.
class Nature
{
public:
    std::map<size_t, VehicleEntity> celestialBodies;
    std::map<size_t, VehicleEntity> strayEntities;
};

// Collection of event ids for not controllable events that occured in simulation.
class EventPoint
{
public:
    size_t entityID;
    std::vector<size_t> eventIDs;
};

// Collection of action ids and particular vehicle id to run.
class VehicleInstruction
{
public:
    size_t vehicleID;
    std::vector<size_t> actionIDs;
};

// Collection of vehicle instructions and particular player id to run.
class PlayerInstruction
{
public:
    size_t playerID;
    std::vector<VehicleInstruction> vehicleInstructions;
};

// Collection of time points and player instructions to run.
class SimInstruction
{
public:
    msecs begin;
    msecs end;
    msecs timeStep;
    std::vector<PlayerInstruction> playerInstructions;
    std::vector<EventPoint> eventPoints;

};

// Manages simulation, players, nature, time and their properties.
class SimDriver
{
public:
    SimDriver();

    Nature nature;
    std::map<size_t, Player> players;
    SimInstruction compiledInstruction;
    TimeDriver time;

    void run();
    void stop();
    void compile();

};

#endif // SIMDRIVER_H
