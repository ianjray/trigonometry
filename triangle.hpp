#pragma once

#include "angle.hpp"

#include <string>

class RightAngledTriangle;

/// Models a triangle with sides @c a, @c b, and @c.
class Triangle
{
public:
    /// Construct triangle with sides @c a, @c b, and @c c.
    Triangle(double a, double b, double c);

    /// Construct triangle with sides @c a and @c b, and angle @c C.
    static Triangle with_a_b_C(double a, double b, const Angle & C);

    /// Construct triangle with angles @c A and @c B, and side @c C.
    static Triangle with_A_B_c(const Angle & A, const Angle & B, double c);

    /// Split triangle into right-angled triangle.
    /// @return New right-angled triangle with angle @c A and hypotenuse @c b.
    RightAngledTriangle subA() const;

    /// Split triangle into right-angled triangle.
    /// @return New right-angled triangle with angle @c B and hypotenuse @c a.
    RightAngledTriangle subB() const;

    /// @return double Angle @c A (which is opposite side @c a).
    Angle A() const;

    /// @return double Angle @c B (which is opposite side @c b).
    Angle B() const;

    /// @return double Angle @c C (which is opposite side @c c).
    Angle C() const;

    /// @return double Length of opposite side @c a.
    double a() const;

    /// @return double Length of adjacent side @c b.
    double b() const;

    /// @return double Length of hypotenuse @c c.
    double c() const;

    /// @return std::string Description.
    std::string description() const;

private:
    Angle A_;
    Angle B_;
    Angle C_;
    double a_;
    double b_;
    double c_;
};
