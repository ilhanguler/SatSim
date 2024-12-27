#pragma once
#ifndef SIMEVENT_H
#define SIMEVENT_H

#include "base_definitions.h"

enum EventType{
    EVENT,
    ACTION,
};

// Base class for all events. Represents non-user defined and simulation driven events.
class Event
{
public:
    Event();
    template <class T>
    void run(T arg);

    size_t id;
    EventType tpye;

    msecs tMinus;
    msecs tAbsolute;

    static size_t count;
};

// Base class for actions. Derived from Event class. Represents user defined actions.
class Action : public Event
{
public:
    Action();

    msecs duration;
};

class BurnOut : public Action{
public:
    BurnOut();
    template <class T>
    void run(T &vehicle);

    PreciseVector3D thrust;
};

class Collision : public Event
{
public:
    Collision();
    template <class T>
    void run(T arg);

};

// Non-user defined event collection
union event{
    Event event;
    Collision collision;
};

// User defined action collection
union action{
    Action action;
    BurnOut burnout;
};

#endif // SIMEVENT_H
