#include "base_definitions.h"

PreciseVector3D::PreciseVector3D(cpp_dec_float_100 x, cpp_dec_float_100 y, cpp_dec_float_100 z){
    this->x = x;
    this->y = y;
    this->z = z;
}

PreciseVector3D::PreciseVector3D(const PreciseVector3D &vec){
    *this = vec;
}

PreciseVector3D::PreciseVector3D(){

}

PreciseVector3D PreciseVector3D::operator+(const PreciseVector3D &vec){
    return PreciseVector3D(x + vec.x, y + vec.y, z + vec.z);
}

PreciseVector3D PreciseVector3D::operator*(cpp_dec_float_100 c){
    return PreciseVector3D(x * c, y * c, z * c);
}

PreciseVector3D PreciseVector3D::operator-(const PreciseVector3D &vec){
    return PreciseVector3D(x - vec.x, y - vec.y, z - vec.z);
}

PreciseVector3D PreciseVector3D::operator/(cpp_dec_float_100 c){
    return PreciseVector3D(x / c, y / c, z / c);
}

PreciseVector3D &PreciseVector3D::operator+=(const PreciseVector3D &vec){
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

PreciseVector3D &PreciseVector3D::operator-=(const PreciseVector3D &vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

PreciseVector3D &PreciseVector3D::operator=(const PreciseVector3D &vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

PreciseVector3D &PreciseVector3D::operator=(cpp_dec_float_100 c){
    x = y = z = c;
    return *this;
}
