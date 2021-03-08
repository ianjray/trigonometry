#pragma once

/// Models an angle in radians or degrees.
class Angle
{
public:
    /// Construct an empty angle (zero radians).
    Angle();

    /// Construct angle in radians.
    static Angle radians(double rad);

    /// Construct angle in degrees.
    static Angle degrees(double deg);

    /// @return double Radians.
    double rad() const;

    /// @return double Degrees.
    double deg() const;

    /// Conversion operator.
    /// @see rad
    /// @return Angle in radians.
    operator double() const;

    Angle & operator+=(const Angle & other);

    Angle & operator-=(const Angle & other);

    Angle & operator/=(double denominator);

    Angle & operator%=(const Angle & other);

    Angle operator+(const Angle & other) const;

    Angle operator-(const Angle & other) const;

    Angle operator/(double denominator) const;

    Angle operator%(const Angle & other) const;

private:
    /// Private constructor.
    /// @see Angle::radians
    /// @see Angle::degrees
    Angle(double rad);

    double rad_;
};
