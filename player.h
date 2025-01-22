#ifndef PLAYER_H
#define PLAYER_H

#include "spaceentity.h"

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
    Player(PlayerType type);

    size_t id;
    PlayerType type;
    std::vector<VehicleEntity> vehicles;

    static size_t count;

};

// Not controllable. It is mother nature.
class Enviroment
{
public:
    Enviroment();

    std::vector<CelestialBody> celestialBodies;
    std::vector<StrayEntity> strayEntities;
};


#endif // PLAYER_H
