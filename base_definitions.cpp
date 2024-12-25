#include "base_definitions.h"

PreciseVector3D::PreciseVector3D(cpp_dec_float_100 x, cpp_dec_float_100 y, cpp_dec_float_100 z){
    this->x = x;
    this->y = y;
    this->z = z;
}

PreciseVector3D::PreciseVector3D(const PreciseVector3D &vec){
    *this = vec;
}

PreciseVector3D::PreciseVector3D(int c){
    *this = c;
}

PreciseVector3D::PreciseVector3D()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

cpp_dec_float_100 PreciseVector3D::get_r(){
    return sqrt(x*x + y*y + z*z);
}

PreciseVector3D PreciseVector3D::operator+(const PreciseVector3D &vec) const{
    return PreciseVector3D(x + vec.x, y + vec.y, z + vec.z);
}

PreciseVector3D PreciseVector3D::operator*(cpp_dec_float_100 c) const{
    return PreciseVector3D(x * c, y * c, z * c);
}

PreciseVector3D PreciseVector3D::operator-(const PreciseVector3D &vec) const{
    return PreciseVector3D(x - vec.x, y - vec.y, z - vec.z);
}

PreciseVector3D PreciseVector3D::operator/(cpp_dec_float_100 c) const{
    return PreciseVector3D(x / c, y / c, z / c);
}

void PreciseVector3D::operator+=(const PreciseVector3D &vec){
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

void PreciseVector3D::operator-=(const PreciseVector3D &vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}

void PreciseVector3D::operator=(const PreciseVector3D &vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void PreciseVector3D::operator=(const int &c){
    x = y = z = c;
}

