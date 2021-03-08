#pragma once

#include "angle.hpp"
#include "point.hpp"

#include <string>

/// Models a vector.
/// @see https://en.wikipedia.org/wiki/Euclidean_vector
/// @discussion Positive directions are counter-clockwise (right-handed Cartesian coordinate system).
class Vector
{
public:
    /// Construct a vector in the standard position (with tail at origin).
    Vector(const Point & head);

    /// Construct a vector from @c tail to @c head.
    /// @see translate
    Vector(const Point & tail, const Point & head);

    /// Construct a vector having @c direction and @c magnitude.
    Vector(const Angle & direction, double magnitude);

    /// Construct vector by rotating @c v by @c direction.
    static Vector rotate(const Vector & v, const Angle & direction);

    /// Construct vector @c v translated to point @c point.
    static Vector translate(const Vector & v, const Point & point);

    /// Mutate vector by rotating by @c direction.
    Vector & rotate(const Angle & direction);

    /// Mutate vector by translating to @c point.
    Vector & translate(const Point & point);

    /// @return Point The initial point.
    Point tail() const;

    /// @return Point The terminal point.
    Point head() const;

    /// Return direction of the vector.
    /// @discussion By convention zero is on the positive @c x axis, and
    /// positive directions move counter-clockwise.
    /// @code
    ///    π/2
    ///     |
    /// π --+-- 0
    ///     |
    ///    3π/2
    /// @endcode
    /// @return Angle The direction.
    Angle direction() const;

    /// @return double The magnitude.
    double magnitude() const;

    /// @return std::string Description.
    std::string description() const;

private:
    Point tail_;
    Point head_;
};
