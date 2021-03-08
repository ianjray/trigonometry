#include "angle.hpp"

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

} // namespace

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

Angle & Angle::operator/=(double denominator)
{
    rad_ = scale(rad_ / denominator);
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

Angle Angle::operator/(double denominator) const
{
    return Angle(rad_ / denominator);
}

Angle Angle::operator%(const Angle & other) const
{
    return Angle(fmod(rad_, other.rad_));
}

#ifdef UNITTEST_ANGLE

#include "fcmp.hpp"

#include "xassert.hpp"

int main()
{
    xassert(fcmp(Angle(), Angle::radians(0)));
    xassert(fcmp(Angle(), Angle::degrees(0)));

    Angle a = Angle::radians(M_PI_2);
    xassert(fcmp(a, M_PI_2));
    xassert(fcmp(a.rad(), M_PI_2));
    xassert(fcmp(a.deg(), 90));

    xassert(fcmp(Angle::degrees(45) + Angle::radians(M_PI_4), Angle::degrees(90)));

    xassert(fcmp(Angle::radians(M_PI) - Angle::degrees(45), Angle::degrees(135)));

    xassert(fcmp(Angle::degrees(135) / 3., Angle::degrees(45)));

    xassert(fcmp(Angle::degrees(135) / 3., Angle::degrees(45)));

    xassert(fcmp(Angle::degrees(365) % Angle::degrees(45), Angle::degrees(5)));

    a = Angle::degrees(90);
    xassert(fcmp(a.rad(), M_PI_2));

    a += Angle::radians(M_PI_2);
    xassert(fcmp(a, M_PI));
    xassert(fcmp(a.rad(), M_PI));
    xassert(fcmp(a.deg(), 180));

    a -= Angle::radians(M_PI_4);
    xassert(fcmp(a.deg(), 135));

    a /= 3;
    xassert(fcmp(a.deg(), 45));

    a += Angle::degrees(90);
    a %= Angle::radians(M_PI_2);
    xassert(fcmp(a.deg(), 45));
}

#endif
