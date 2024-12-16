#ifndef SPACEENTITY_H
#define SPACEENTITY_H

#include <qcontainerfwd.h>
#include <Qvector>
#include <qvariant.h>

#include "base_definitions.h"

#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

// Every property is calculated as SI unit.

class SpaceEntity
{
public:
    SpaceEntity();

    QString id();
    QString name();

    // trajectory is for precise calculations. gui_trajectory is for gui.
    std::vector<PreciseVector3D> trajectory;
    std::vector<QVector3D> gui_trajectory();

    // position is for precise calculations. gui_pos is for gui.
    QVector3D gui_pos();

    PreciseVector3D position;
    PreciseVector3D velocity;
    PreciseVector3D acceleration;
    PreciseVector3D jerk;
    PreciseVector3D snap;
    PreciseVector3D crack;

    PreciseVector3D force;

    cpp_dec_float_100 mass;

};

class StrayEntity : public SpaceEntity
{
public:

};

class VehicleEntity : public SpaceEntity
{
public:

    // Direction where the vehicle is facing towards;
    // Spherical Coordinate System {r, angle(x), angle(z)} or proportional unit vector;
    // This is not viable for the current situation because of complexity and deadline. I will implement it later.
    PreciseVector3D bearing;

    PreciseVector3D thrust;
    PreciseVector3D prop_thrust;

    cpp_dec_float_100 net_mass;

    cpp_dec_float_100 max_thrust;
    cpp_dec_float_100 fuel_cons_per_sec;
    cpp_dec_float_100 fuel;

    cpp_dec_float_100 max_prop_thrust;
    cpp_dec_float_100 prop_cons_per_sec;
    cpp_dec_float_100 prop_fuel;

    // twr: thrust to weight ratio
    cpp_dec_float_100 twr;
    // delta_v: remaining max velocity gain
    cpp_dec_float_100 delta_v;
    cpp_dec_float_100 radio_range;

    // isotropic = 0, directional = 1 (dish)
    int antenna;
};

class CelestialBody : public SpaceEntity
{
public:

    // mass * Gravitational constant
    cpp_dec_float_100 mG;

    // Path equation is needed or we must calculate this too.
};

#endif // SPACEENTITY_H
