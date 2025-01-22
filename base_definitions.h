#ifndef BASE_DEFINITIONS_H
#define BASE_DEFINITIONS_H

#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

// Gravitational Constant N⋅(m^2)⋅(kg^−2) SI Unit, according to latest researches
const cpp_dec_float_100 GConst("6.67430e-11");

const long long lightSpeed = 299792458;

typedef long long msecs;


class PreciseVector3D
{
    public:
    PreciseVector3D(const cpp_dec_float_100 &x, const cpp_dec_float_100 &y, const cpp_dec_float_100 &z);
    PreciseVector3D(const PreciseVector3D &vec);
    PreciseVector3D(int c);
    PreciseVector3D();

    cpp_dec_float_100 get_scalar();
    // Convert Spherical Coordinates to Unit Vector
    PreciseVector3D csctuv();

    cpp_dec_float_100 x = 0;
    cpp_dec_float_100 y = 0;
    cpp_dec_float_100 z = 0;

    PreciseVector3D operator+ (const PreciseVector3D &vec) const;

    PreciseVector3D operator- (const PreciseVector3D &vec) const;

    PreciseVector3D operator/ (const cpp_dec_float_100 &c) const;

    PreciseVector3D operator* (const cpp_dec_float_100 &c) const;

    void operator+= (const PreciseVector3D &vec);

    void operator-= (const PreciseVector3D &vec);

    void operator= (const PreciseVector3D &vec);

    void operator= (PreciseVector3D &&vec);

    void operator=(int c);

    bool operator<(int c);

    bool operator==(int c);

    bool operator!=(int c);

    bool operator>(int c);
};

// Euler angle based rotation system
class EulerRotation{
public:
    float x;
    float y;
    float z;
};

#endif // BASE_DEFINITIONS_H
