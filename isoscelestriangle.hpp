#pragma once

#include "angle.hpp"

#include <string>

/// Models an isosceles triangle.
/// ```
///        +
///       /V\       .
/// side /   \ side .
///     /     \     .
///    /B     B\    .
///   +---------+
///       base
/// ```
class IsoscelesTriangle
{
public:
    /// Construct triangle with vertex angle @c V and side length @c side.
    IsoscelesTriangle(const Angle & V, double side);

    /// @return double Vertex angle @c V.
    Angle vertexAngle() const;

    /// @return double Computed base angle.
    Angle baseAngle() const;

    /// @return double Length of side.
    double side() const;

    /// @return double Computed length of base.
    double base() const;

    /// @return double Computed height.
    double height() const;

    /// @return std::string Description.
    std::string description() const;

private:
    Angle V_;
    double side_;
};
