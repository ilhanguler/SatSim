#include "simcore.h"

PreciseVector3D SimCore::calcOneBody_Force(const CelestialBody &cb, const SpaceEntity &se){
    return calcOneBody_Accel(cb, se) * se.mass;;
}

PreciseVector3D SimCore::calcOneBody_Accel(const CelestialBody &cb, const SpaceEntity &se){
    cpp_dec_float_100 mG_r3 = cb.mG / pow<3>((cb.position - se.position).get_scalar());
    return PreciseVector3D(mG_r3*(cb.position.x - se.position.x),
                           mG_r3*(cb.position.y - se.position.y),
                           mG_r3*(cb.position.z - se.position.z));
}

void SimCore::calcTwoBody_Accel(CelestialBody &cb_1, CelestialBody &cb_2){
    cpp_dec_float_100 mG_r3 = cb_1.mG / pow<3>((cb_1.position - cb_2.position).get_scalar());
    PreciseVector3D accel(mG_r3*(cb_1.position.x - cb_2.position.x),
                          mG_r3*(cb_1.position.y - cb_2.position.y),
                          mG_r3*(cb_1.position.z - cb_2.position.z));

    cb_2.acceleration += accel;
    cb_1.acceleration += accel * (cb_2.mass / cb_1.mass);
}

void SimCore::sgpTaylorForEntities(const std::vector<CelestialBody> &cbs, SpaceEntity &se,
                      const msecs deltaMSecs, const msecs simLengthByMSecs){

    size_t it = simLengthByMSecs / deltaMSecs;

    PreciseVector3D a_temp;
    PreciseVector3D j_temp;

    for(size_t i = 0; i < it; i++){
        a_temp = se.acceleration;
        j_temp = se.jerk;
        se.acceleration = 0;

        for(auto &cb: cbs){
            se.acceleration += calcOneBody_Accel(cb, se);
        }

        se.jerk = (se.acceleration - a_temp) / dT;
        se.snap = (se.jerk - j_temp) / dT;
        se.position += se.velocity * dT + se.acceleration * dT2 + se.jerk * dT3 + se.snap * dT4;
        se.velocity += se.acceleration * dT + se.jerk * dT2 + se.snap * dT3;

        se.trajectory.push_back(se.position);
    }
}

void SimCore::sgpTaylorForVehicles(const std::vector<CelestialBody> &cbs, VehicleEntity &ve,
                                const msecs deltaMSecs, const msecs simLengthByMSecs){

    size_t it = simLengthByMSecs / deltaMSecs;

    PreciseVector3D a_temp;
    PreciseVector3D j_temp;

    for(size_t i = 0; i < it; i++){
        a_temp = ve.acceleration;
        j_temp = ve.jerk;
        ve.acceleration = 0;

        for(auto &cb: cbs){
            ve.acceleration += calcOneBody_Accel(cb, ve);
        }

        ve.jerk = (ve.acceleration - a_temp) / dT;
        ve.snap = (ve.jerk - j_temp) / dT;
        ve.position += ve.velocity * dT + ve.acceleration * dT2 + ve.jerk * dT3 + ve.snap * dT4;
        ve.velocity += ve.acceleration * dT + ve.jerk * dT2 + ve.snap * dT3;

        ve.trajectory.push_back(ve.position);
    }
}

void SimCore::sgpTaylorNBody(std::vector<CelestialBody> &cbs, std::pair<size_t, size_t> boundary, const msecs deltaMSecs, const msecs simLengthByMSecs){

    size_t it = simLengthByMSecs / deltaMSecs;

    std::vector<PreciseVector3D> a_temps;
    PreciseVector3D j_temp;


    for(size_t i = 0; i < it; i++){

        for(auto &cb: cbs){
            a_temps.push_back(cb.acceleration);
            cb.acceleration = 0;
        }

        for(size_t f = cbs.size() - 1; f !=-1; f--){
            CelestialBody &cb_1 = cbs.at(f);
            for(size_t s = f; s != -1; s--){
                CelestialBody &cb_2 = cbs.at(s);
                calcTwoBody_Accel(cb_1, cb_2);
            }

        }

        for(size_t k = cbs.size() - 1; k != -1; k--){
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

void SimCore::sgpTaylorSingleCore(std::vector<CelestialBody> &cbs, std::map<size_t, Player> &ps, std::vector<StrayEntity> &ses, const msecs deltaMSecs, const msecs simLengthByMSecs)
{
    size_t it = simLengthByMSecs / deltaMSecs;

    PreciseVector3D a_temp;
    PreciseVector3D j_temp;

    std::vector<PreciseVector3D> a_temps;

    for(size_t i = 0; i < it; i++){

        // Calculations for SpaceEntity
        for(auto &se : ses){
            a_temp = se.acceleration;
            j_temp = se.jerk;
            se.acceleration = 0;

            for(auto &cb: cbs){
                se.acceleration += calcOneBody_Accel(cb, se);
            }

            se.jerk = (se.acceleration - a_temp) / dT;
            se.snap = (se.jerk - j_temp) / dT;
            se.position += se.velocity * dT + se.acceleration * dT2 + se.jerk * dT3 + se.snap * dT4;
            se.velocity += se.acceleration * dT + se.jerk * dT2 + se.snap * dT3;

            se.trajectory.push_back(se.position);
        }

        // Players
        for(auto &p : ps){
            // Calculations for VehicleEntity
            for(auto &ve : p.second.vehicles){
                a_temp = ve.acceleration;
                j_temp = ve.jerk;
                ve.acceleration = 0;

                for(auto &cb: cbs){
                    ve.acceleration += calcOneBody_Accel(cb, ve);
                }

                ve.jerk = (ve.acceleration - a_temp) / dT;
                ve.snap = (ve.jerk - j_temp) / dT;
                ve.position += ve.velocity * dT + ve.acceleration * dT2 + ve.jerk * dT3 + ve.snap * dT4;
                ve.velocity += ve.acceleration * dT + ve.jerk * dT2 + ve.snap * dT3;

                ve.trajectory.push_back(ve.position);
            }
        }

        // Calculations for CelestialBody
        for(auto &cb: cbs){
            a_temps.push_back(cb.acceleration);
            cb.acceleration = 0;
        }

        for(size_t f = cbs.size() - 1; f !=-1; f--){
            CelestialBody &cb_1 = cbs.at(f);
            for(size_t s = f; s != -1; s--){
                CelestialBody &cb_2 = cbs.at(s);
                calcTwoBody_Accel(cb_1, cb_2);
            }

        }

        for(size_t k = cbs.size() - 1; k != -1; k--){
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

void SimCore::initDTs(const msecs deltaMSecs)
{
    dT = (cpp_dec_float_100)(deltaMSecs)/(1000);
    dT2 = pow<2>(dT) / 2;
    dT3 = pow<3>(dT) / 6;
    dT4 = pow<4>(dT) / 24;

}
