#include "spaceentity.h"

// Static members

size_t SpaceEntity::entityCount = 0;
size_t StrayEntity::strayCount = 0;
size_t VehicleEntity::vehicleCount = 0;
size_t CelestialBody::celestialCount = 0;

SpaceEntity::SpaceEntity()
{
    entityCount++;
}

StrayEntity::StrayEntity(const PreciseVector3D &position,
                         const cpp_dec_float_100 &mass,
                         const cpp_dec_float_100 &radius,
                         const QString &name,
                         const PreciseVector3D &velocity)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
    this->name = name;
    this->velocity = velocity;

    id = strayCount;

    strayCount++;
    entityCount++;
}

VehicleEntity::VehicleEntity(const PreciseVector3D &position,
                             const cpp_dec_float_100 &mass,
                             const cpp_dec_float_100 &radius,
                             const QString &name,
                             const PreciseVector3D &velocity,
                             const cpp_dec_float_100 &maxThrust,
                             const cpp_dec_float_100 &fuelConsPerMSec,
                             const cpp_dec_float_100 &fuel,
                             const AntennaType &antenna,
                             const cpp_dec_float_100 &antennaGain,
                             const PreciseVector3D &bearing)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
    this->name = name;
    this->velocity = velocity;
    this->maxThrust = maxThrust;
    this->fuelConsPerMSec = fuelConsPerMSec;
    this->fuel = fuel;
    this->antenna = antenna;
    this->antennaGain = antennaGain;
    this->bearing = bearing;

    id = vehicleCount;
    twr = maxThrust / mass;

    vehicleCount++;
    entityCount++;
}

void VehicleEntity::startThruster(msecs timeMSecs)
{
    auto tItr = thrusters.find(timeMSecs);
    if(tItr != thrusters.end()){
        thrust = bearingUnitScale * tItr->second.thrust;
        _thrusterActivation = (thrust != 0);
    }
}

void VehicleEntity::runThruster(const msecs deltaMSecs)
{

    if(_thrusterActivation == 0){
        return;
    }

    // Updating thrust related properties.
    if(fuel > 0){
        cpp_dec_float_100 fuelUsedEstimated = fuelConsPerMSec * deltaMSecs;
        cpp_dec_float_100 fuelUsedReal;
        cpp_dec_float_100 futureMass;

        if(fuelUsedEstimated > fuel){
            fuelUsedReal = fuel;
            futureMass = mass - fuelUsedReal;
            fuel = 0;
            acceleration = (thrust / ((mass + futureMass) / 2)) * (fuelUsedReal / fuelUsedEstimated);
            mass = futureMass;
        }
        else{
            fuelUsedReal = fuelUsedEstimated;
            fuel -= fuelUsedReal;
            futureMass = mass - fuelUsedReal;
            acceleration = thrust / ((mass + futureMass) / 2);
            mass = futureMass;
        }
    }
    else{
        acceleration = 0;
    }
}

void VehicleEntity::setBearing(cpp_dec_float_100 inclation, cpp_dec_float_100 azimuth)
{
    bearing.y = inclation;
    bearing.z = azimuth;
    bearingUnitScale = bearing.csctuv();
}

void VehicleEntity::calculateTwr()
{
    twr = maxThrust / (acceleration.get_scalar() * mass);
}

CelestialBody::CelestialBody(PreciseVector3D position,
                             cpp_dec_float_100 mass,
                             const cpp_dec_float_100 &radius,
                             QString name,
                             PreciseVector3D velocity)
{
    this->position = position;
    this->mass = mass;
    this->radius = radius;
    this->name = name;
    this->velocity = velocity;

    mG = mass * GConst;

    id = celestialCount;

    celestialCount++;
    entityCount++;
}

