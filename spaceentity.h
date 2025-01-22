#ifndef SPACEENTITY_H
#define SPACEENTITY_H

#include <qvariant.h>
#include <qvectornd.h>
#include <vector>
#include <map>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "base_definitions.h"
#include "event.h"

using namespace boost::multiprecision;

enum Status{
    DESTROYED,
    UNKNOWN,
    LIVE
};

enum AntennaType
{
    NOT_AVAILABLE,
    ISOTROPIC,
    DIRECTIONAL
};

// Every property is calculated as SI unit.
// Base class for all objects in space.
class SpaceEntity
{
public:

    SpaceEntity();

    size_t id;
    QString name;
    Status status = Status::LIVE;

    // Calculated precise raw trajectory points.
    std::vector<PreciseVector3D> trajectory;

    // Scaled trajectory points for GUI.
    std::vector<QVector3D> guiTrajectory;

    // Calculated precise raw position.
    PreciseVector3D position;

    // Scaled position for GUI.
    QVector3D guiPos;

    PreciseVector3D velocity;
    PreciseVector3D acceleration;
    PreciseVector3D jerk;
    PreciseVector3D snap;
    PreciseVector3D crack;

    PreciseVector3D force;

    cpp_dec_float_100 mass;
    cpp_dec_float_100 radius;

    // Sorted by time points.
    std::multimap<msecs, Collision> collisions;
    int _collision;

    static size_t entityCount;

};

// Represents any object that is not controllable by humanity and has not considerable effect on other objects in space.
class StrayEntity : public SpaceEntity
{
public:

    StrayEntity(const PreciseVector3D &position, const cpp_dec_float_100 &mass, const cpp_dec_float_100 &radius, const QString &name = "",
                const PreciseVector3D &velocity = 0);

    static size_t strayCount;
};

// Represents any object that is controllable by humanity in space.
class VehicleEntity : public SpaceEntity
{
public:

    VehicleEntity(const PreciseVector3D &position,
                  const cpp_dec_float_100 &mass,
                  const cpp_dec_float_100 &radius,
                  const QString &name = "",
                  const PreciseVector3D &velocity = 0,
                  const cpp_dec_float_100 &maxThrust = 0,
                  const cpp_dec_float_100 &fuelConsPerMSec = 0,
                  const cpp_dec_float_100 &fuel = 0,
                  const AntennaType &antenna = AntennaType::NOT_AVAILABLE,
                  const cpp_dec_float_100 &antennaGain  = 0,
                  const PreciseVector3D &bearing = 0);

    // Sets thrusters.
    void startThruster(const msecs timeMSecs);
    // Calculates thruster effects.
    void runThruster(const msecs deltaMSecs);

    // Sets bearing
    void setBearing(cpp_dec_float_100 inclation, cpp_dec_float_100 azimuth);

    // Calculate TWR
    void calculateTwr();

    // Direction where the vehicle is facing towards;
    // Spherical Coordinate System {r, inclation(x), azimuth(z)} or proportional unit vector;
    PreciseVector3D bearing;
    // Unit vector of bearing for calculations.
    PreciseVector3D bearingUnitScale;

    PreciseVector3D thrust;
    cpp_dec_float_100 thrustScalar;

    cpp_dec_float_100 netMass;

    cpp_dec_float_100 maxThrust;
    cpp_dec_float_100 fuelConsPerMSec;
    cpp_dec_float_100 fuel;

    // twr: thrust to weight ratio
    cpp_dec_float_100 twr;
    // deltaV: remaining max velocity gain
    cpp_dec_float_100 deltaV;

    AntennaType antenna;
    cpp_dec_float_100 antennaGain;

    // Sorted by time points.
    std::multimap<msecs, Thruster> thrusters;
    // Activation flag for thrusters
    int _thrusterActivation = 0;

    static size_t vehicleCount;
};

// Represents celestial mass body.
class CelestialBody : public SpaceEntity
{
public:

    // Path equation is needed or we must calculate this too.
    // Apparently we will calculate trajectory.
    CelestialBody(PreciseVector3D position,
                  cpp_dec_float_100 mass,
                  const cpp_dec_float_100 &radius,
                  QString name = "",
                  PreciseVector3D velocity = 0);

    // mass * Gravitational constant (G * m)
    // Pre-calculated for optimization.
    cpp_dec_float_100 mG;

    static size_t celestialCount;
};

#endif // SPACEENTITY_H
