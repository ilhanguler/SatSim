#ifndef EVENT_H
#define EVENT_H

#include "base_definitions.h"

// Request flag for change of time step value.
// REVERT : Set to default.
// NO_PREF : Does not matter.
// CHANGE : Set to another one.
enum TimeStepRequest{
    REVERT = -1,
    NO_PREF = 0,
    CHANGE = 1
};

// Events are standalone events that happens at one time.
// To neutralize the effects of events, you have to create another one to counter the effects of it.

// Base class for all events. Represents user defined and simulation driven events.
// We will refer player defined events as actions, natural events as events.
class EventBase
{
public:
    EventBase();
    EventBase(size_t id_pair, msecs timeMSecs, msecs duration,
              msecs timeStep, TimeStepRequest request);
    size_t id;

    // The reason behind this is that compilation of events into executable format in simulation driver,
    // requires creation and management of unnecessary datas that exist in event class allready!.
    // That way we will define events as pairs to overcome this problem.
    size_t id_pair;

    msecs timeMSecs;
    msecs duration;
    msecs timeStep;
    int activation = 0;

    TimeStepRequest request;

    static size_t count;
};

// Event to burnout engines (thrusters).
class Thruster : public EventBase
{
public:
    Thruster();
    Thruster(size_t id_pair, msecs timeMSecs, msecs duration,
             msecs timeStep, TimeStepRequest request, cpp_dec_float_100 thrust);

    cpp_dec_float_100 thrust;
};

// Event of detection of possible collision.
class Collision : public EventBase
{
public:
    Collision();

};

/* DEPRECATED IDEA

// Every event type has to be registered here.
enum EventType{
    COLLISION,
    BURNOUT
};

// Event collection. Every event has to be registered here.
class Event : public EventBase{
public:
    Event();
    Event(const Event &e);
    Event(size_t id, size_t id_pair, msecs timeMSecs, msecs duration, msecs timeStep, TimeStepRequest request);

    template<class T>
    void execute(T &entity){
        switch (type) {
        case EventType::COLLISION:
            collision.run(entity);
            break;
        default:
            break;
        }
    }
    EventType type;

    union{
        Collision collision;
    };

};

// Collection of user defined events.
class Action : public EventBase{
public:
    Action();
    Action(const Action &e);

    template<class T>
    void execute(T &entity){
        switch (type) {
        case EventType::BURNOUT:
            burnout.run(entity);
            break;

        default:
            break;
        }
    }
    EventType type;

    union{
        BurnOut burnout;
    };
};
*/
#endif // SIMEVENT_H
