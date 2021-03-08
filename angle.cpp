#include "angle.h"

#include <cmath>

#ifndef M_TWOPI
#define M_TWOPI (2.0 * M_PI)
#endif


Angle::Angle() : rad_{}
{
}

Angle Angle::radians(double rad)
{
    return Angle(rad);
}

Angle Angle::degrees(double deg)
{
    return Angle(deg / 360. * M_TWOPI);
}

namespace
{

/// @return Radians in the range 0..2π.
double scale(double rad)
{
    while (rad < 0)        rad += M_TWOPI;
    while (rad >= M_TWOPI) rad -= M_TWOPI;
    return rad;
}

}

Angle::Angle(double rad)
{
    rad_ = scale(rad);
}

double Angle::rad() const
{
    return rad_;
}

double Angle::deg() const
{
    return rad_ * 360. / M_TWOPI;
}

Angle::operator double() const
{
    return rad_;
}

Angle & Angle::operator+=(const Angle & other)
{
    rad_ = scale(rad_ + other.rad_);
    return *this;
}

Angle & Angle::operator-=(const Angle & other)
{
    rad_ = scale(rad_ - other.rad_);
    return *this;
}

Angle & Angle::operator%= (const Angle & other)
{
    rad_ = scale(fmod(rad_, other.rad_));
    return *this;
}

Angle Angle::operator+(const Angle & other) const
{
    return Angle(rad_ + other.rad_);
}

Angle Angle::operator-(const Angle & other) const
{
    return Angle(rad_ - other.rad_);
}

Angle Angle::operator%(const Angle & other) const
{
    return Angle(fmod(rad_, other.rad_));
}

#ifdef UNITTEST_ANGLE

#include "fcmp.h"
#include <cassert>

//@unittest clang++ -std=c++17 -DUNITTEST_ANGLE -Wall fcmp.cpp
int main()
{
    assert(fcmp(Angle(), Angle::radians(0)));
    assert(fcmp(Angle(), Angle::degrees(0)));

    Angle a = Angle::radians(M_PI_2);
    assert(fcmp(a, M_PI_2));
    assert(fcmp(a.rad(), M_PI_2));
    assert(fcmp(a.deg(), 90));

    assert(fcmp(Angle::degrees(45) + Angle::radians(M_PI_4), Angle::degrees(90)));

    assert(fcmp(Angle::radians(M_PI) - Angle::degrees(45), Angle::degrees(135)));

    assert(fcmp(Angle::degrees(365) % Angle::degrees(45), Angle::degrees(5)));

    a = Angle::degrees(90);
    assert(fcmp(a.rad(), M_PI_2));

    a += Angle::radians(M_PI_2);
    assert(fcmp(a, M_PI));
    assert(fcmp(a.rad(), M_PI));
    assert(fcmp(a.deg(), 180));

    a -= Angle::radians(M_PI_4);
    assert(fcmp(a.deg(), 135));

    a %= Angle::radians(M_PI_2);
    assert(fcmp(a.deg(), 45));
}

#endif
