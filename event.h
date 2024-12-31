#pragma once
#ifndef SIMEVENT_H
#define SIMEVENT_H

#include "base_definitions.h"

// Every event type has to be registered here.
enum EventType{
    COLLISION,
    BURNOUT
};

// Request flag for change of time step value.
// DEFAULT : Set to default.
// NO_PREF : Does not matter.
// CHANGE : Set to another one.
enum TimeStepRequest{
    DEFAULT = -1,
    NO_PREF = 0,
    CHANGE = 1
};

// Events are standalone events that happens at one time.
// To neutralize the effects of events, you have to create another one to counter the effects of it.

// Base class for all events. Represents user defined and simulation driven events.
class EventBase
{
public:
    EventBase();

    size_t id;

    // The reason behind this is that compilation of events into executable format in simulation driver,
    // requires creation and management of unnecessary datas that exist in event class allready!.
    // That way we will define events as pairs to overcome this problem.
    size_t id_pair;

    msecs tMinus;
    msecs tAbsolute;
    msecs duration;
    msecs timeStep;

    TimeStepRequest request;

    static size_t count;
};

class BurnOut{
public:
    BurnOut();
    template <class T>
    void run(T &vehicle);

    PreciseVector3D thrust;
};

class Collision
{
public:
    Collision();
    template <class T>
    void run(T arg);

};

// Event collection. Every event has to be registered here.
class Event : public EventBase{
public:
    EventType type;

    union{
        Collision collision;
        BurnOut burnout;
    };
};

#endif // SIMEVENT_H
