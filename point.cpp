#include "point.hpp"

#include "fcmp.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>

Point::Point() : x_{}, y_{}
{
}

Point::Point(double x, double y) : x_{x}, y_{y}
{
}

double Point::x() const
{
    return x_;
}

double Point::y() const
{
    return y_;
}

bool Point::operator==(const Point & other)
{
    return fcmp(x_, other.x_) && fcmp(y_, other.y_);
}

bool Point::operator!=(const Point & other)
{
    return !operator==(other);
}

Point & Point::operator+=(const Point & other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Point & Point::operator-=(const Point & other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

Point Point::operator+(const Point & rhs) const
{
    Point lhs(*this);
    lhs += rhs;
    return lhs;
}

Point Point::operator-(const Point & rhs) const
{
    Point lhs(*this);
    lhs -= rhs;
    return lhs;
}

std::string Point::description() const
{
    std::stringstream ss;
    ss << "Point "
        "(" << x() << ", " << y() << ")";
    return ss.str();
}

#ifdef UNITTEST_POINT

#include "xassert.hpp"

int main()
{
    xassert(fcmp(Point().x(), 0));
    xassert(fcmp(Point().y(), 0));
    xassert(Point() == Point(0, 0));
    xassert(Point() != Point(1, 1));
    xassert(fcmp(Point(3, 4).x(), 3));
    xassert(fcmp(Point(3, 4).y(), 4));

    auto a = Point(1, 2);
    a += Point(10, 20);
    xassert(a == Point(11, 22));

    auto b = Point(10, 20);
    b -= Point(1, 2);
    xassert(b == Point(9, 18));

    a = Point(1, 2);
    b = Point(10, 20);
    xassert(a + b == Point(11, 22));
    xassert(b - a == Point(9, 18));

    xassert(a.description() == std::string("Point (1, 2)"));
}

#endif
