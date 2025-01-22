#include "player.h"

// ===== Player ===== This section belongs to Player.

// Static Player members
size_t Player::count = 0;

Player::Player()
{
    id = count;
    count++;
}

Player::Player(PlayerType type) :  type(type)
{
    id = count;
    count++;
}

// ===== Enviroment ===== This section belongs to Enviroment.

Enviroment::Enviroment()
{

}
