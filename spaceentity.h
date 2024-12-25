#ifndef SPACEENTITY_H
#define SPACEENTITY_H

#include <qcontainerfwd.h>
#include <Qvector>
#include <qvariant.h>
#include <vector>

#include "base_definitions.h"

#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

// Every property is calculated as SI unit.

class SpaceEntity
{
public:

    SpaceEntity();

    QString id;
    QString name;

    // destroyed = -1, unknown = 0, live = 1,
    int status = 1;

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

    static size_t entity_count;

};

class StrayEntity : public SpaceEntity
{
public:

    StrayEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString id = "", QString name = "",
                PreciseVector3D velocity = 0);

    static size_t stray_count;
};

class VehicleEntity : public SpaceEntity
{
public:

    VehicleEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString id = "", QString name = "",
                  PreciseVector3D velocity = 0, cpp_dec_float_100 max_thrust = 0, cpp_dec_float_100 fuel_cons_per_sec = 0,
                  cpp_dec_float_100 fuel = 0, cpp_dec_float_100 max_prop_thrust = 0, cpp_dec_float_100 prop_cons_per_sec = 0,
                  cpp_dec_float_100 prop_fuel = 0, int antenna_type = -1, cpp_dec_float_100 antenna_gain = 0, PreciseVector3D bearing = 0);

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

    static size_t vehicle_count;
};

class CelestialBody : public SpaceEntity
{
public:

    // Path equation is needed or we must calculate this too.
    CelestialBody(PreciseVector3D position, cpp_dec_float_100 mass, QString id = "", QString name = "",
                  PreciseVector3D velocity = 0);

    // mass * Gravitational constant (m * G)
    cpp_dec_float_100 GM;

    static size_t celestial_count;
};


#endif // SPACEENTITY_H
