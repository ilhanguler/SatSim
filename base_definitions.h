#ifndef BASE_DEFINITIONS_H
#define BASE_DEFINITIONS_H

#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

// Gravitational Constant N⋅(m^2)⋅(kg^−2) SI Unit, according to latest researches
const cpp_dec_float_100 GConst("6.67430e-11");

class PreciseVector3D
{
    public:
    PreciseVector3D(cpp_dec_float_100 x, cpp_dec_float_100 y ,cpp_dec_float_100 z);

    PreciseVector3D(const PreciseVector3D &vec);

    PreciseVector3D(int c);

    PreciseVector3D();

    cpp_dec_float_100 x;
    cpp_dec_float_100 y;
    cpp_dec_float_100 z;

    cpp_dec_float_100 get_r();

    PreciseVector3D operator+ (const PreciseVector3D &vec) const;

    PreciseVector3D operator* (cpp_dec_float_100 c) const;

    PreciseVector3D operator- (const PreciseVector3D &vec) const;

    PreciseVector3D operator/ (cpp_dec_float_100 c) const;

    void operator+= (const PreciseVector3D &vec);

    void operator-= (const PreciseVector3D &vec);

    void operator= (const PreciseVector3D &vec);

    void operator=(const int &c);
};

class Vector3D{
public:
    double x;
    double y;
    double z;
};

#endif // BASE_DEFINITIONS_H
