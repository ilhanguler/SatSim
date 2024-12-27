#include "spaceentity.h"

size_t SpaceEntity::entityCount = 0;
size_t StrayEntity::strayCount = 0;
size_t VehicleEntity::vehicleCount = 0;
size_t CelestialBody::celestialCount = 0;

SpaceEntity::SpaceEntity()
{
    entityCount++;
}

StrayEntity::StrayEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString name,
                         PreciseVector3D velocity)
{
    this->position = position;
    this->mass = mass;
    this->name = name;
    this->velocity = velocity;

    id = strayCount;

    strayCount++;
    entityCount++;
}

VehicleEntity::VehicleEntity(PreciseVector3D position, cpp_dec_float_100 mass, QString name,
                             PreciseVector3D velocity, cpp_dec_float_100 max_thrust, cpp_dec_float_100 fuel_cons_per_sec,
                             cpp_dec_float_100 fuel, cpp_dec_float_100 max_prop_thrust, cpp_dec_float_100 prop_cons_per_sec,
                             cpp_dec_float_100 prop_fuel, int antenna_type, cpp_dec_float_100 antenna_gain, PreciseVector3D bearing)
{
    this->position = position;
    this->mass = mass;
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

    id = vehicleCount;

    vehicleCount++;
    entityCount++;
}

CelestialBody::CelestialBody(PreciseVector3D position, cpp_dec_float_100 mass, QString name,
                             PreciseVector3D velocity)
{
    this->position = position;
    this->mass = mass;
    this->name = name;
    this->velocity = velocity;

    GM = mass * GConst;

    id = celestialCount;

    celestialCount++;
    entityCount++;
}

