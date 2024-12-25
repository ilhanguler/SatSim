#include "spaceentity.h"

size_t SpaceEntity::entity_count = 0;
size_t StrayEntity::stray_count = 0;
size_t VehicleEntity::vehicle_count = 0;
size_t CelestialBody::celestial_count = 0;

SpaceEntity::SpaceEntity()
{
    entity_count++;
}

StrayEntity::StrayEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString id, QString name,
                         PreciseVector3D velocity)
{
    this->position = position;
    this->mass = mass;
    this->id = id;
    this->name = name;
    this->velocity = velocity;

    stray_count++;
}

VehicleEntity::VehicleEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString id, QString name,
                             PreciseVector3D velocity, cpp_dec_float_100 max_thrust, cpp_dec_float_100 fuel_cons_per_sec,
                             cpp_dec_float_100 fuel, cpp_dec_float_100 max_prop_thrust, cpp_dec_float_100 prop_cons_per_sec,
                             cpp_dec_float_100 prop_fuel, int antenna_type, cpp_dec_float_100 antenna_gain, PreciseVector3D bearing)
{
    this->position = position;
    this->mass = mass;
    this->id = id;
    this->name = name;
    this->velocity = velocity;
    this->max_thrust = max_thrust;
    this->fuel_cons_per_sec = fuel_cons_per_sec;
    this->fuel = fuel;
    this->max_prop_thrust = max_prop_thrust;
    this->prop_cons_per_sec = prop_cons_per_sec;
    this->prop_fuel = prop_fuel;
    this->antenna_type = antenna_type;
    this->antenna_gain = antenna_gain;
    this->bearing = bearing;

    vehicle_count++;
}

CelestialBody::CelestialBody(PreciseVector3D position, cpp_dec_float_100 mass, QString id, QString name,
                             PreciseVector3D velocity)
{
    this->position = position;
    this->mass = mass;
    this->id = id;
    this->name = name;
    this->velocity = velocity;
    GM = mass * GConst;

    celestial_count++;
}

