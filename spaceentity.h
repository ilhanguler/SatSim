#pragma once
#ifndef SPACEENTITY_H
#define SPACEENTITY_H

#include <qcontainerfwd.h>
#include <Qvector>
#include <qvariant.h>
#include <vector>

#include "base_definitions.h"
#include "event.h"

#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

enum Status{
    DESTROYED,
    UNKNOWN,
    LIVE
};

// Every property is calculated as SI unit.
// Base class for all objects in space.
class SpaceEntity
{
public:

    SpaceEntity();

    size_t id;
    QString name;

    Status status;

    // Calculated precise raw trajectory points.
    std::vector<PreciseVector3D> trajectory;

    // Scaled trajectory points for GUI.
    std::vector<Vector3D> gui_trajectory;

    // Scaled position for GUI.
    Vector3D gui_pos;

    // Calculated precise raw position.
    PreciseVector3D position;

    PreciseVector3D velocity;
    PreciseVector3D acceleration;
    PreciseVector3D jerk;
    PreciseVector3D snap;
    PreciseVector3D crack;

    PreciseVector3D force;

    cpp_dec_float_100 mass;

    std::map<size_t, event> naturalEvents;
    static size_t entityCount;

};

// Represents any object that is not controllable by humanity and has not considerable effect on other objects in space.
class StrayEntity : public SpaceEntity
{
public:

    StrayEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString name = "",
                PreciseVector3D velocity = 0);

    static size_t strayCount;
};

// Represents any object that is controllable by humanity in space.
class VehicleEntity : public SpaceEntity
{
public:

    VehicleEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString name = "",
                  PreciseVector3D velocity = 0, cpp_dec_float_100 max_thrust = 0, cpp_dec_float_100 fuel_cons_per_sec = 0,
                  cpp_dec_float_100 fuel = 0, cpp_dec_float_100 max_prop_thrust = 0, cpp_dec_float_100 prop_cons_per_sec = 0,
                  cpp_dec_float_100 prop_fuel = 0, int antenna_type = -1, cpp_dec_float_100 antenna_gain = 0, PreciseVector3D bearing = 0);

    void runAction(action &act);

    // Direction where the vehicle is facing towards;
    // Spherical Coordinate System {r, angle(x), angle(z)} or proportional unit vector;
    // This is not viable for the current situation because of complexity and deadline. I will implement it later.
    PreciseVector3D bearing;

    cpp_dec_float_100 net_mass;

    PreciseVector3D thrust;
    cpp_dec_float_100 max_thrust;
    cpp_dec_float_100 fuel_cons_per_sec;
    cpp_dec_float_100 fuel;

    PreciseVector3D prop_thrust;
    cpp_dec_float_100 max_prop_thrust;
    cpp_dec_float_100 prop_cons_per_sec;
    cpp_dec_float_100 prop_fuel;

    // twr: thrust to weight ratio
    cpp_dec_float_100 twr;
    // delta_v: remaining max velocity gain
    cpp_dec_float_100 delta_v;

    // no antenna = -1, isotropic = 0, directional = 1,
    int antenna_type;
    cpp_dec_float_100 antenna_gain;

    std::map<size_t, action> actions;

    static size_t vehicleCount;
};

// Represents celestial mass body.
class CelestialBody : public SpaceEntity
{
public:

    // Path equation is needed or we must calculate this too.
    // Apparently we will calculate trajectory.
    CelestialBody(PreciseVector3D position, cpp_dec_float_100 mass, QString name = "",
                  PreciseVector3D velocity = 0);

    // mass * Gravitational constant (G * m)
    // Pre-calculated for optimization.
    cpp_dec_float_100 GM;

    static size_t celestialCount;
};

#endif // SPACEENTITY_H
