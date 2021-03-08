#pragma once

#include <string>

class Point
{
public:
    /// Construct an empty point (0,0).
    Point();

    /// Construct a point (x,y).
    Point(double x, double y);

    /// @return x.
    double x() const;

    /// @return y.
    double y() const;

    bool operator==(const Point & other);

    bool operator!=(const Point & other);

    Point & operator+=(const Point & other);

    Point & operator-=(const Point & other);

    Point operator+(const Point & rhs) const;

    Point operator-(const Point & rhs) const;

    /// @return std::string Description.
    std::string description() const;

private:
    double x_;
    double y_;
};
