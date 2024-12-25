#ifndef PERTURBATIONS_H
#define PERTURBATIONS_H

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/special_functions/pow.hpp>

#include "base_definitions.h"
#include "spaceentity.h"

using namespace boost::multiprecision;
using namespace boost::math;

namespace sgp
{

// Position difference between body and entity is V[a, b, c];
// Acceleration and force vector that applies to space entity is V[aq, bq, cq];
// q is proportional distribution unit of acceleration between dimensions
// g = m*G/r^2;
// g^2 = (aq)^2 + (bq)^2 + (cq)^2  --->  q = g / sqrt(a^2 + b^2 + c^2);
// Therefore we can say q = mG/r and calculate acceleration vector easily.
// Calculates and returns acceleration for one body.
PreciseVector3D calcOneBody_Accel(const CelestialBody& cb, const SpaceEntity& se);

// Look at calcOneBody_Accel function
// Calculates and returns force (Newton) for one body.
PreciseVector3D calcOneBody_Force(const CelestialBody& cb, const SpaceEntity& se);

// Calculates acceleration for two bodies and sets their acceleration vectors.
void calcTwoBody(CelestialBody &cb_1, CelestialBody &cb_2);

// Braindead solution with some optimizations.
// Calculates trajectory for one small body that is insignificant for the system.
void sgpTaylorOneBody(const std::vector<CelestialBody>& cbs, SpaceEntity &se,
               cpp_dec_float_100 deltaMSecs, cpp_dec_float_100 simLengthByHours);

// Calculates trajectory for the given set of celestial bodies.
// In short, solves N body problem.
void sgpTaylorNBody(std::vector<CelestialBody>& cbs, cpp_dec_float_100 deltaMSecs, cpp_dec_float_100 simLengthByHours);

}

// dV = A*t + (1/2)J*t^3 + (1/3!)K*t^3 ...
// dS = V*t + (1/2)A*t^2 + (1/3!)J*t^3 + (1/4!)K*t^4 + (1/5!)L*t^5 + ... + (1/n!)S'n*t^n
// ^This is an example for perturbation with Taylor Series.
// Calculations may start with very small steps to calculate essential values for perturbation, then the step size would expand
// Alternative way is calculating with basic methods with smaller step size such as Euler method.
// Another alternative way is using RK4 or Leapfrog-Vertel methods. Leapfrog-Vertel are conserving energy, others don't.
// Accuracy: Classic Taylor Series > Leapfrog-Verlet > RK4 > Euler

#endif // PERTURBATIONS_H
