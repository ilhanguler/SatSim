#include "base_definitions.h"

PreciseVector3D::PreciseVector3D(const cpp_dec_float_100 &x, const cpp_dec_float_100 &y, const cpp_dec_float_100 &z) :
    x(x), y(y), z(z)
{

}

PreciseVector3D::PreciseVector3D(const PreciseVector3D &vec){
    *this = vec;
}

PreciseVector3D::PreciseVector3D(int c){
    *this = c;
}

PreciseVector3D::PreciseVector3D()
{

}

cpp_dec_float_100 PreciseVector3D::get_scalar(){
    return sqrt(x*x + y*y + z*z);
}

PreciseVector3D PreciseVector3D::csctuv()
{
    return PreciseVector3D(sin(y) * cos(z), sin(y) * sin(z), cos(y));
}

PreciseVector3D PreciseVector3D::operator+(const PreciseVector3D &vec) const{
    return PreciseVector3D(x + vec.x, y + vec.y, z + vec.z);
}

PreciseVector3D PreciseVector3D::operator-(const PreciseVector3D &vec) const{
    return PreciseVector3D(x - vec.x, y - vec.y, z - vec.z);
}

PreciseVector3D PreciseVector3D::operator/(const cpp_dec_float_100 &c) const{
    return PreciseVector3D(x / c, y / c, z / c);
}

PreciseVector3D PreciseVector3D::operator*(const cpp_dec_float_100 &c) const{
    return PreciseVector3D(x * c, y * c, z * c);
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

void PreciseVector3D::operator=(PreciseVector3D &&vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

bool PreciseVector3D::operator<(int c)
{
    return (x < c && y < c && z < c);
}

bool PreciseVector3D::operator==(int c)
{
    return (x == c && y == c && z == c);
}

bool PreciseVector3D::operator!=(int c)
{
    return (x != c && y != c && z != c);
}

bool PreciseVector3D::operator>(int c)
{
    return (x > c && y > c && z > c);
}

void PreciseVector3D::operator=(int c){
    x = y = z = c;
}

