#include "event.h"


EventBase::EventBase() {}


BurnOut::BurnOut()
{

}

Collision::Collision()
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
