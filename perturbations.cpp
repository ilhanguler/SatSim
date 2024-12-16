#include "perturbations.h"

namespace sgp {

void sgpTaylor(const std::vector<CelestialBody> &cbs, SpaceEntity &se, cpp_dec_float_100 dT){

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

PreciseVector3D calcOneBody_Force(const CelestialBody &cb, const SpaceEntity &se){
    cpp_dec_float_100 mmG = cb.mG * se.mass;
    return PreciseVector3D(mmG*(cb.position.x-se.position.x),
                           mmG*(cb.position.y-se.position.y),
                           mmG*(cb.position.z-se.position.z));
}

PreciseVector3D calcOneBody_Accel(const CelestialBody &cb, const SpaceEntity &se){
    return PreciseVector3D(cb.mG*(cb.position.x-se.position.x),
                           cb.mG*(cb.position.y-se.position.y),
                           cb.mG*(cb.position.z-se.position.z));
}

}
