#pragma once


/// @brief Models an angle in radians or degrees.
class Angle
{
public:
    /// @brief Construct an empty angle (zero radians).
    Angle();

    /// @brief Construct angle in radians.
    static Angle radians(double rad);

    /// @brief Construct angle in degrees.
    static Angle degrees(double deg);

    /// @return double Radians.
    double rad() const;

    /// @return double Degrees.
    double deg() const;

    /// @brief Conversion operator.
    /// @see rad
    /// @return Angle in radians.
    operator double() const;

    Angle & operator+=(const Angle & other);

    Angle & operator-=(const Angle & other);

    Angle & operator%=(const Angle & other);

    Angle operator+(const Angle & other) const;

    Angle operator-(const Angle & other) const;

    Angle operator%(const Angle & other) const;

private:
    /// @brief Private constructor.
    /// @see Angle::radians
    /// @see Angle::degrees
    Angle(double rad);

    double rad_;
};
