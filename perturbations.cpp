#include "perturbations.h"

namespace sgp {


PreciseVector3D calcOneBody_Force(const CelestialBody &cb, const SpaceEntity &se){
    return calcOneBody_Accel(cb, se) * se.mass;;
}

PreciseVector3D calcOneBody_Accel(const CelestialBody &cb, const SpaceEntity &se){
    cpp_dec_float_100 GM_r = cb.GM / (cb.position - se.position).get_scalar();
    return PreciseVector3D(GM_r*(cb.position.x-se.position.x),
                           GM_r*(cb.position.y-se.position.y),
                           GM_r*(cb.position.z-se.position.z));
}

void calcTwoBody(CelestialBody &cb_1, CelestialBody &cb_2){
    cpp_dec_float_100 GM_r = cb_1.GM / (cb_1.position - cb_2.position).get_scalar();
    PreciseVector3D accel(GM_r*(cb_1.position.x-cb_2.position.x),
                          GM_r*(cb_1.position.y-cb_2.position.y),
                          GM_r*(cb_1.position.z-cb_2.position.z));

    cb_2.acceleration += accel;
    cb_1.acceleration += (accel * cb_2.mass) / cb_1.mass;
}

void sgpTaylorOneBody(const std::vector<CelestialBody>& cbs, SpaceEntity &se,
                      cpp_dec_float_100 deltaMSecs, cpp_dec_float_100 simLengthByHours){

    cpp_dec_float_100 dT = deltaMSecs/1000;
    cpp_dec_float_100 dT2 = pow<2>(dT) / 2;
    cpp_dec_float_100 dT3 = pow<3>(dT) / 6;
    cpp_dec_float_100 dT4 = pow<4>(dT) / 24;

    size_t it = ((simLengthByHours*60*60)/dT).convert_to<size_t>();

    PreciseVector3D a_temp;
    PreciseVector3D j_temp;

    for(size_t i = 0; i < it; i++){
        a_temp = se.acceleration;
        j_temp = se.jerk;
        se.acceleration = 0;

        for(auto cb: cbs){
            se.acceleration += calcOneBody_Accel(cb, se);
        }

        se.jerk = (se.acceleration - a_temp) / dT;
        se.snap = (se.jerk - j_temp) / dT;
        se.position += se.velocity * dT + se.acceleration * dT2 + se.jerk * dT3 + se.snap * dT4;
        se.velocity += se.acceleration * dT + se.jerk * dT2 + se.snap * dT3;

        se.trajectory.push_back(se.position);
    }
}

void sgpTaylorNBody(std::vector<CelestialBody>& cbs, cpp_dec_float_100 deltaMSecs, cpp_dec_float_100 simLengthByHours){

    cpp_dec_float_100 dT = deltaMSecs/1000;
    cpp_dec_float_100 dT2 = pow<2>(dT) / 2;
    cpp_dec_float_100 dT3 = pow<3>(dT) / 6;
    cpp_dec_float_100 dT4 = pow<4>(dT) / 24;

    size_t it = ((simLengthByHours*60*60)/dT).convert_to<size_t>();

    std::vector<PreciseVector3D> a_temps;
    PreciseVector3D j_temp;


    for(size_t i = 0; i < it; i++){

        for(auto cb: cbs){
            a_temps.push_back(cb.acceleration);
            cb.acceleration = 0;
        }

        for(size_t f = 0; f < cbs.size(); f++){
            CelestialBody &cb_1 = cbs.at(f);

            for(size_t s = f + 1; s < cbs.size(); s++){
                CelestialBody &cb_2 = cbs.at(s);
                calcTwoBody(cb_1, cb_2);
            }

        }

        for(size_t k = 0; k < cbs.size(); k++){
            CelestialBody &cb = cbs.at(k);
            PreciseVector3D &a_temp = a_temps.at(k);
            j_temp = cb.jerk;

            cb.jerk = (cb.acceleration - a_temp) / dT;
            cb.snap = (cb.jerk - j_temp) / dT;
            cb.position += cb.velocity * dT + cb.acceleration * dT2 + cb.jerk * dT3 + cb.snap * dT4;
            cb.velocity += cb.acceleration * dT + cb.jerk * dT2 + cb.snap * dT3;

            cb.trajectory.push_back(cb.position);
        }

        a_temps.clear();
    }
}
}
