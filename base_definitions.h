#ifndef BASE_DEFINITIONS_H
#define BASE_DEFINITIONS_H

#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

// Gravitational Constant N⋅(m^2)⋅(kg^−2) SI Unit, according to latest researches
const cpp_dec_float_100 GConst("6.67430e−11");

class PreciseVector3D
{
    public:
    PreciseVector3D(cpp_dec_float_100 x, cpp_dec_float_100 y ,cpp_dec_float_100 z){
        this->x = x;
        this->y = y;
        this->z = z;
    };

    PreciseVector3D(PreciseVector3D const& vec){
        *this = vec;
    };

    cpp_dec_float_100 x;
    cpp_dec_float_100 y;
    cpp_dec_float_100 z;

    PreciseVector3D operator+ (PreciseVector3D const& vec){
        return PreciseVector3D(x + vec.x, y + vec.y, z + vec.z);
    }

    PreciseVector3D operator* (cpp_dec_float_100 c){
        return PreciseVector3D(x * c, y * c, z * c);
    }

    PreciseVector3D operator- (PreciseVector3D const& vec){
        return PreciseVector3D(x - vec.x, y - vec.y, z - vec.z);
    }

    PreciseVector3D operator/ (cpp_dec_float_100 c){
        return PreciseVector3D(x / c, y / c, z / c);
    }

    PreciseVector3D& operator+= (PreciseVector3D const& vec){
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    PreciseVector3D& operator-= (PreciseVector3D const& vec){
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }

    PreciseVector3D& operator= (PreciseVector3D const& vec){
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }

    PreciseVector3D& operator= (cpp_dec_float_100 c){
        x = y = z = c;
        return *this;
    }
};

#endif // BASE_DEFINITIONS_H
