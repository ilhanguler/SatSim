// TODO: Implement multithreading solution for SGP

#ifndef SIMCORE_H
#define SIMCORE_H

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/special_functions/pow.hpp>

#include "base_definitions.h"
#include "spaceentity.h"
#include "player.h"

using namespace boost::multiprecision;
using namespace boost::math;

class SimCore
{
public:
    // Position difference between body and entity is V[a, b, c];
    // Acceleration and force vector that applies to space entity is V[aq, bq, cq];
    // q is proportional distribution unit of acceleration between dimensions;
    // g = m*G/r^2;
    // g^2 = (aq)^2 + (bq)^2 + (cq)^2  --->  q = g / sqrt(a^2 + b^2 + c^2);
    // Therefore we can say q = mG/r^3 and calculate acceleration vector easily.
    // Calculates and returns acceleration for one body.
    PreciseVector3D calcOneBody_Accel(const CelestialBody &cb, const SpaceEntity &se);

    // Look at calcOneBody_Accel function
    // Calculates and returns force (Newton) for one body.
    PreciseVector3D calcOneBody_Force(const CelestialBody &cb, const SpaceEntity &se);

    // Calculates acceleration for two bodies and sets their acceleration vectors.
    void calcTwoBody_Accel(CelestialBody &cb_1, CelestialBody &cb_2);

    // Braindead solution with some optimizations.
    // Calculates trajectory for one small body that is insignificant for the system.
    void sgpTaylorForEntities(const std::vector<CelestialBody> &cbs, SpaceEntity &se,
                          const msecs deltaMSecs, const msecs simLengthByMSecs);

    // Braindead solution with some optimizations.
    // Calculates trajectory for one small body that is insignificant for the system.
    void sgpTaylorForVehicles(const std::vector<CelestialBody> &cbs, VehicleEntity &ve,
                               const msecs deltaMSecs, const msecs simLengthByMSecs);

    // Calculates trajectory for the given set of celestial bodies.
    // In short, solves N body problem.
    void sgpTaylorNBody(std::vector<CelestialBody> &cbs, std::pair<size_t, size_t> boundary, const msecs deltaMSecs, const msecs simLengthByMSecs);

    // Runs simulation on single core.
    void sgpTaylorSingleCore(std::vector<CelestialBody> &cbs, std::map<size_t, Player> &ps, std::vector<StrayEntity> &ses, const msecs deltaMSecs, const msecs simLengthByMSecs);

    // Pre-calculating deltaTime and its powers with coefficients for optimization.
    // This function has to be called when deltaMSecs is changed.
    void initDTs(const msecs deltaMSecs);

    cpp_dec_float_100 dT = 0;
    cpp_dec_float_100 dT2 = 0;
    cpp_dec_float_100 dT3 = 0;
    cpp_dec_float_100 dT4 = 0;

    msecs deltaMSecs = 1000;
    msecs deltaMSecsDefault = 1000;
    msecs simLengthByMsecs = 0;
};

// dV = A*t + (1/2)J*t^3 + (1/3!)K*t^3 ...
// dS = V*t + (1/2)A*t^2 + (1/3!)J*t^3 + (1/4!)K*t^4 + (1/5!)L*t^5 + ... + (1/n!)S'n*t^n
// ^This is an example for perturbation with Taylor Series.
// Calculations may start with very small steps to calculate essential values for perturbation, then the step size would expand
// Alternative way is calculating with basic methods with smaller step size such as Euler method.
// Another alternative way is using RK4 or Leapfrog-Vertel methods. Leapfrog-Vertel are conserving energy, others don't.
// Accuracy: Classic Taylor Series > Leapfrog-Verlet > RK4 > Euler

// Verlet integration can be used if we know two positions between delta time of an object.
// If we know only initial position, then we have to know initial velocity to calculate the position after delta time.
// Verlet uses velocity only at start, then puts it aside and does calculations with other properties.

#endif // SIMCORE_H
