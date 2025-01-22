#include "event.h"

// Static EventBase members.

size_t EventBase::count = 0;

EventBase::EventBase() {}

EventBase::EventBase(size_t id_pair, msecs timeMSecs, msecs duration, msecs timeStep, TimeStepRequest request)
    : id_pair(id_pair), timeMSecs(timeMSecs), duration(duration),
    timeStep(timeStep), request(request)
{

}


Thruster::Thruster()
{

}

Thruster::Thruster(size_t id_pair, msecs timeMSecs, msecs duration, msecs timeStep, TimeStepRequest request, cpp_dec_float_100 thrust)
    : EventBase(id_pair, timeMSecs, duration, timeStep, request), thrust(thrust)
{

}

Collision::Collision()
{

}

/* DEPRECATED IDEA
Event::Event()
{

}

Event::Event(const Event &e)
{
    type = e.type;
    duration = e.duration;
    id = e.id;
    id_pair = e.id_pair;
    request = e.request;
    timeMSecs = e.timeMSecs;
    tMinus = e.tMinus;
    timeStep = e.timeStep;

    switch (type) {
    case EventType::COLLISION:
        collision = e.collision;
        break;
    default:
        break;
    }
}

Action::Action()
{

}

Action::Action(const Action &e)
{
    type = e.type;
    duration = e.duration;
    id = e.id;
    id_pair = e.id_pair;
    request = e.request;
    timeMSecs = e.timeMSecs;
    tMinus = e.tMinus;
    timeStep = e.timeStep;

    switch (type) {
    case EventType::COLLISION:
        burnout = e.burnout;
        break;
    default:
        break;
    }
}
*/
