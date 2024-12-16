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

    PreciseVector3D(PreciseVector3D const& vec);

    PreciseVector3D();

    cpp_dec_float_100 x;
    cpp_dec_float_100 y;
    cpp_dec_float_100 z;

    PreciseVector3D operator+ (PreciseVector3D const& vec);

    PreciseVector3D operator* (cpp_dec_float_100 c);

    PreciseVector3D operator- (PreciseVector3D const& vec);

    PreciseVector3D operator/ (cpp_dec_float_100 c);

    PreciseVector3D& operator+= (PreciseVector3D const& vec);

    PreciseVector3D& operator-= (PreciseVector3D const& vec);

    PreciseVector3D& operator= (PreciseVector3D const& vec);

    PreciseVector3D& operator= (cpp_dec_float_100 c);
};

#endif // BASE_DEFINITIONS_H
