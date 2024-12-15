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
// Therefore we can say q = mG and calculate acceleration vector easily.
// This is a form of extreme optimization.
PreciseVector3D calcOneBody_Accel(const CelestialBody& cb, const SpaceEntity& se){
    return PreciseVector3D(cb.mG*(cb.position.x-se.position.x),
                           cb.mG*(cb.position.y-se.position.y),
                           cb.mG*(cb.position.z-se.position.z));
}

// Look at calcOneBody_Accel function
PreciseVector3D calcOneBody_Force(const CelestialBody& cb, const SpaceEntity& se){
    cpp_dec_float_100 mmG = cb.mG * se.mass;
    return PreciseVector3D(mmG*(cb.position.x-se.position.x),
                           mmG*(cb.position.y-se.position.y),
                           mmG*(cb.position.z-se.position.z));
}

// Braindead solution with extreme(!) optimizations
void taylorPerturbation(const std::vector<CelestialBody>& cbs, SpaceEntity& se, cpp_dec_float_50 dT){

    cpp_dec_float_100 dT2 = pow<2>(dT)/cpp_dec_float_100(2);
    cpp_dec_float_100 dT3 = pow<3>(dT)/cpp_dec_float_100(6);
    cpp_dec_float_100 dT4 = pow<4>(dT)/cpp_dec_float_100(24);

    PreciseVector3D a_(0,0,0);
    PreciseVector3D j_(0,0,0);

    for(quint64 i; i < 5400;i++){
        a_ = se.acceleration;
        j_ = se.jerk;
        se.acceleration = 0;

        se.position += se.velocity * dT + se.acceleration * dT2 + se.jerk * dT3 + se.snap * dT4;
        se.velocity += se.acceleration * dT + se.jerk * dT2 + se.snap * dT3;

        for(auto cb: cbs){
            se.acceleration += calcOneBody_Accel(cb, se);
        }
        se.jerk = (se.acceleration - a_) / dT;
        se.snap = se.jerk - j_ / dT;
    }
}

}

// dV = A*t + (1/2)J*t^3 + (1/3!)K*t^3 ...
// dS = V*t + (1/2)A*t^2 + (1/3!)J*t^3 + (1/4!)K*t^4 + (1/5!)L*t^5 + ... + (1/n!)S'n*t^n
// ^This is an example for perturbation with Taylor Series.
// Calculations may start with very small steps to calculate essential values for perturbation, then the step size would expand
// Alternative way is calculating with basic methods with smaller step size such as Euler method.
// Another alternative way is using RK4 or Leapfrog-Vertel methods. Leapfrog-Vertel are conserving energy, others don't.
// Accuracy: Classic Taylor Series > Leapfrog-Verlet > RK4 > Euler

#endif // PERTURBATIONS_H
