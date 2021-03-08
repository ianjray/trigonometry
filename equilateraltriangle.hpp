#pragma once

#include "angle.hpp"

#include <string>

/// Models an equilateral triangle.
/// ```
///        +
///       /A\       .
/// side /   \ side .
///     /     \     .
///    /A     A\    .
///   +---------+
///       side
/// ```
class EquilateralTriangle
{
public:
    /// Construct equilateral triangle with side length @c side.
    EquilateralTriangle(double side);

    /// @return double Internal angle.
    Angle angle() const;

    /// @return double Length of side.
    double side() const;

    /// @return double Computed height.
    double height() const;

    /// @return std::string Description.
    std::string description() const;

private:
    double side_;
};
