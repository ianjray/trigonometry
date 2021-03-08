#pragma once

#include "angle.hpp"

#include <string>

/// Models a right-angled triangle.
/// @discussion The triangle is comprised of opposite side @c a, adjacent side @c b, and hypotenuse @c c.
/// Angle @c C (opposite side @c) is 90 degrees by definition.
/// ```
///   +
///   |\     .
///   |B\    .
/// a |  \ c .
///   |   \  .
///   |"  A\ .
///   +-----+
///      b
/// ```
class RightAngledTriangle
{
public:
    /// Construct right-angled triangle with sides @c a and @c b.
    static RightAngledTriangle with_a_b(double a, double b);

    /// Construct right-angled triangle with sides @c a and @c c.
    static RightAngledTriangle with_a_c(double a, double c);

    /// Construct right-angled triangle with angle @c A and hypotenuse @c c.
    static RightAngledTriangle with_A_c(const Angle & A, double c);

    /// Construct right-angled triangle from existing triangle @c r, with new opposite side @c a.
    static RightAngledTriangle with_a(const RightAngledTriangle &, double a);

    /// Construct right-angled triangle from existing triangle @c r, with new adjacent side @c b.
    static RightAngledTriangle with_b(const RightAngledTriangle &, double b);

    /// Construct right-angled triangle from existing triangle @c r, with new hypotenuse @c c.
    static RightAngledTriangle with_c(const RightAngledTriangle &, double c);

    /// @return double Angle @c A (which is opposite side @c a).
    Angle A() const;

    /// @return double Angle @c B (which is opposite side @c b).
    Angle B() const;

    /// @return double Length of opposite side @c a.
    double a() const;

    /// @return double Length of adjacent side @c b.
    double b() const;

    /// @return double Length of hypotenuse @c c.
    double c() const;

    /// @return std::string Description.
    std::string description() const;

private:
    /// Private constructor.
    /// @discussion Factory methods are used to create instances of right-angled triangle.
    RightAngledTriangle(double a, double b, double c);

    Angle A_;
    double a_;
    double b_;
    double c_;
};
