#include "vector.h"

#include "rightangledtriangle.h"
#include "triangle.h"
#include <cmath>
#include <iomanip>
#include <sstream>


Vector::Vector(const Point & head) : tail_{}, head_{head}
{
}

Vector::Vector(const Point & tail, const Point & head) : tail_{tail}, head_{head}
{
}

Vector::Vector(const Angle & direction, double magnitude)
{
    // Build a right-angled triangle having theta (< 90°) in order to find dx,dy.
    auto t = RightAngledTriangle::with_A_c(direction % Angle::radians(M_PI_2), magnitude);

    //  (-,+) | (+,+)
    // -------+------
    //  (-,-) | (+,-)

    double dx{}, dy{};

    int quadrant = static_cast<int>(direction.rad() / M_PI_2);
    switch (quadrant) {
        case 0:
            dx =  t.b();
            dy =  t.a();
            break;
        case 1:
            dx = -t.a();
            dy =  t.b();
            break;
        case 2:
            dx = -t.b();
            dy = -t.a();
            break;
        case 3:
            dx =  t.a();
            dy = -t.b();
            break;
    }

    tail_ = Point{};
    head_ = Point{dx, dy};
}

Vector Vector::rotate(const Vector & v, const Angle & direction)
{
    return Vector{v.direction() + direction, v.magnitude()};
}

Vector Vector::translate(const Vector & v, const Point & point)
{
    return Vector{point + v.tail(), point + v.head()};
}

Vector & Vector::rotate(const Angle & direction)
{
    *this = rotate(*this, direction);
    return *this;
}

Vector & Vector::translate(const Point & point)
{
    *this = translate(*this, point);
    return *this;
}

Point Vector::tail() const
{
    return tail_;
}

Point Vector::head() const
{
    return head_;
}

namespace
{

/// @return @c x squared.
inline double sqr(double x)
{
    return pow(x, 2);
}

/// @return Integer quadrant in the range 0..3.
int quadrant(double dx, double dy)
{
    //   II | I
    // -----+-----
    //  III | IV

    if (dy >= 0) {
        if (dx >= 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (dx < 0) {
            return 2;
        } else {
            return 3;
        }
    }
}

}

Angle Vector::direction() const
{
    auto dx = head().x() - tail().x();
    auto dy = head().y() - tail().y();

    auto q = quadrant(dx, dy);
    double opp, adj;

    if (q == 0 || q == 2) {
        opp = fabs(dy);
        adj = fabs(dx);
    } else {
        opp = fabs(dx);
        adj = fabs(dy);
    }

    if (fpclassify(opp) == FP_ZERO && fpclassify(adj) == FP_ZERO) {
        return Angle::radians(0);
    }

    return Angle::radians(atan(opp / adj) + M_PI_2 * q);
}

double Vector::magnitude() const
{
    auto dx = head().x() - tail().x();
    auto dy = head().y() - tail().y();

    return sqrt(sqr(dx) + sqr(dy));
}

std::string Vector::description() const
{
    std::stringstream ss;
    ss << "Vector "
        "(" << tail().x() << ", " << tail().y() << "), "
        "(" << head().x() << ", " << head().y() << "); "
        << direction() << " (" << direction().deg() << "°), "
        << magnitude();
    return ss.str();
}


#ifdef UNITTEST_VECTOR

#include "fcmp.h"
#include <cassert>

//@unittest clang++ -std=c++17 -DUNITTEST_VECTOR -Wall angle.cpp fcmp.cpp point.cpp rightangledtriangle.cpp triangle.cpp
int main()
{
    // Constructors, accessors.
    {
        assert(fcmp(Vector(Point(  0,   0)).direction(), Angle::degrees(0)));
        assert(fcmp(Vector(Point( 10,   0)).direction(), Angle::degrees(0)));
        assert(fcmp(Vector(Point( 10,  10)).direction(), Angle::degrees(45)));
        assert(fcmp(Vector(Point(  0,  10)).direction(), Angle::degrees(90)));
        assert(fcmp(Vector(Point(-10,  10)).direction(), Angle::degrees(135)));
        assert(fcmp(Vector(Point(-10,   0)).direction(), Angle::degrees(180)));
        assert(fcmp(Vector(Point(-10, -10)).direction(), Angle::degrees(225)));
        assert(fcmp(Vector(Point(  0, -10)).direction(), Angle::degrees(270)));

        assert(fcmp(Vector(Point( 3,  4)).magnitude(), 5));
        assert(fcmp(Vector(Point(-3,  4)).magnitude(), 5));
        assert(fcmp(Vector(Point(-3, -4)).magnitude(), 5));
        assert(fcmp(Vector(Point( 3, -4)).magnitude(), 5));

        assert(fcmp(Vector(Point( 3,  4)).direction(), Angle::radians(atan(4./3.))));

        auto u = Vector(Point{2, 3});
        assert(u.tail() == Point());
        assert(u.head() == Point(2, 3));

        auto v = Vector(Point{5, 5}, Point{7, 8});
        assert(v.tail() == Point(5, 5));
        assert(v.head() == Point(7, 8));
        assert(fcmp(v.direction(), u.direction()));
        assert(fcmp(v.magnitude(), u.magnitude()));

        auto w = Vector(u.direction(), u.magnitude());
        assert(w.tail() == u.tail());
        assert(w.head() == u.head());
        assert(fcmp(w.direction(), u.direction()));
        assert(fcmp(w.magnitude(), u.magnitude()));
    }

    // Factory methods.
    {
        auto u = Vector(Point{2, 3});
        auto v = Vector(Point{-3, 2});

        auto w = Vector::rotate(u, Angle::radians(M_PI_2));
        assert(w.tail() == v.tail());
        assert(w.head() == v.head());

        w = Vector::rotate(w, Angle::radians(2 * M_PI - M_PI_2));
        assert(w.tail() == u.tail());
        assert(w.head() == u.head());

        w = Vector::translate(u, Point{});
        assert(w.tail() == u.tail());
        assert(w.head() == u.head());

        v = Vector(Point{-1, -1}, Point{1, 2});
        assert(fcmp(v.direction(), u.direction()));
        assert(fcmp(v.magnitude(), u.magnitude()));

        w = Vector::translate(w, Point{-1, -1});
        assert(fcmp(w.direction(), v.direction()));
        assert(fcmp(w.magnitude(), v.magnitude()));
    }

    // Chaining methods.
    {
        auto u = Vector(Point{3, 4});

        auto v = Vector(Angle::degrees(90), 5).rotate(u.direction()).translate(u.head());
        assert(v.head() == Point(-1, 7));
        assert(fcmp(v.direction(), u.direction() + Angle::degrees(90)));
        assert(fcmp(v.magnitude(), 5));

        auto w = Vector(Angle::degrees(90), 5).rotate(v.direction()).translate(v.head());
        assert(w.head() == Point(-4, 3));
        assert(fcmp(w.direction(), v.direction() + Angle::degrees(90)));
        assert(fcmp(w.magnitude(), 5));

        v = w;
        w = Vector(Angle::degrees(90), 5).rotate(v.direction()).translate(v.head());
        assert(w.head() == Point());
        assert(fcmp(w.direction(), v.direction() + Angle::degrees(90)));
        assert(fcmp(w.magnitude(), 5));

        v = w;
        w = Vector(Angle::degrees(90), 5).rotate(v.direction()).translate(v.head());
        assert(w.head() == Point(3, 4));
        assert(fcmp(w.direction(), u.direction()));
        assert(fcmp(w.magnitude(), 5));

        v = Vector(u.head(), Point{7, 1});
        assert(fcmp(v.direction(), u.direction() - Angle::degrees(90)));
        assert(fcmp(v.magnitude(), 5));

        w = u;
        w.rotate(Angle::degrees(-90)).translate(u.head());
        assert(w.tail() == v.tail());
        assert(w.head() == v.head());
        assert(fcmp(w.direction(), v.direction()));
        assert(fcmp(w.magnitude(), v.magnitude()));
    }

    assert(Vector(Point(3, 4)).description() == std::string("Vector (0, 0), (3, 4); 0.927295 (53.1301°), 5"));
}

#endif
