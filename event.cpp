#include "event.h"

template<class T>
void Event::run(T arg)
{

}

template<class T>
void BurnOut::run(T &vehicle)
{
    vehicle.thrust = thrust;
}

template<class T>
void Collision::run(T arg)
{

}

Event::Event() {}


Action::Action()
{

}

BurnOut::BurnOut()
{

}

Collision::Collision()
{

}
