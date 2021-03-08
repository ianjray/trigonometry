#include "vector.hpp"

#include "rightangledtriangle.hpp"
#include "triangle.hpp"

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

} // namespace

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

    if (std::fpclassify(opp) == FP_ZERO && std::fpclassify(adj) == FP_ZERO) {
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

#include "fcmp.hpp"

#include "xassert.hpp"

int main()
{
    // Constructors, accessors.
    {
        xassert(fcmp(Vector(Point(  0,   0)).direction(), Angle::degrees(0)));
        xassert(fcmp(Vector(Point( 10,   0)).direction(), Angle::degrees(0)));
        xassert(fcmp(Vector(Point( 10,  10)).direction(), Angle::degrees(45)));
        xassert(fcmp(Vector(Point(  0,  10)).direction(), Angle::degrees(90)));
        xassert(fcmp(Vector(Point(-10,  10)).direction(), Angle::degrees(135)));
        xassert(fcmp(Vector(Point(-10,   0)).direction(), Angle::degrees(180)));
        xassert(fcmp(Vector(Point(-10, -10)).direction(), Angle::degrees(225)));
        xassert(fcmp(Vector(Point(  0, -10)).direction(), Angle::degrees(270)));

        xassert(fcmp(Vector(Point( 3,  4)).magnitude(), 5));
        xassert(fcmp(Vector(Point(-3,  4)).magnitude(), 5));
        xassert(fcmp(Vector(Point(-3, -4)).magnitude(), 5));
        xassert(fcmp(Vector(Point( 3, -4)).magnitude(), 5));

        xassert(fcmp(Vector(Point( 3,  4)).direction(), Angle::radians(atan(4./3.))));

        auto u = Vector(Point{2, 3});
        xassert(u.tail() == Point());
        xassert(u.head() == Point(2, 3));

        auto v = Vector(Point{5, 5}, Point{7, 8});
        xassert(v.tail() == Point(5, 5));
        xassert(v.head() == Point(7, 8));
        xassert(fcmp(v.direction(), u.direction()));
        xassert(fcmp(v.magnitude(), u.magnitude()));

        auto w = Vector(u.direction(), u.magnitude());
        xassert(w.tail() == u.tail());
        xassert(w.head() == u.head());
        xassert(fcmp(w.direction(), u.direction()));
        xassert(fcmp(w.magnitude(), u.magnitude()));
    }

    ; // https://github.com/llvm/llvm-project/issues/51706

    // Factory methods.
    {
        auto u = Vector(Point{2, 3});
        auto v = Vector(Point{-3, 2});

        auto w = Vector::rotate(u, Angle::radians(M_PI_2));
        xassert(w.tail() == v.tail());
        xassert(w.head() == v.head());

        w = Vector::rotate(w, Angle::radians(2 * M_PI - M_PI_2));
        xassert(w.tail() == u.tail());
        xassert(w.head() == u.head());

        w = Vector::translate(u, Point{});
        xassert(w.tail() == u.tail());
        xassert(w.head() == u.head());

        v = Vector(Point{-1, -1}, Point{1, 2});
        xassert(fcmp(v.direction(), u.direction()));
        xassert(fcmp(v.magnitude(), u.magnitude()));

        w = Vector::translate(w, Point{-1, -1});
        xassert(fcmp(w.direction(), v.direction()));
        xassert(fcmp(w.magnitude(), v.magnitude()));
    }

    ; // https://github.com/llvm/llvm-project/issues/51706

    // Chaining methods.
    {
        auto u = Vector(Point{3, 4});

        auto v = Vector(Angle::degrees(90), 5).rotate(u.direction()).translate(u.head());
        xassert(v.head() == Point(-1, 7));
        xassert(fcmp(v.direction(), u.direction() + Angle::degrees(90)));
        xassert(fcmp(v.magnitude(), 5));

        auto w = Vector(Angle::degrees(90), 5).rotate(v.direction()).translate(v.head());
        xassert(w.head() == Point(-4, 3));
        xassert(fcmp(w.direction(), v.direction() + Angle::degrees(90)));
        xassert(fcmp(w.magnitude(), 5));

        v = w;
        w = Vector(Angle::degrees(90), 5).rotate(v.direction()).translate(v.head());
        xassert(w.head() == Point());
        xassert(fcmp(w.direction(), v.direction() + Angle::degrees(90)));
        xassert(fcmp(w.magnitude(), 5));

        v = w;
        w = Vector(Angle::degrees(90), 5).rotate(v.direction()).translate(v.head());
        xassert(w.head() == Point(3, 4));
        xassert(fcmp(w.direction(), u.direction()));
        xassert(fcmp(w.magnitude(), 5));

        v = Vector(u.head(), Point{7, 1});
        xassert(fcmp(v.direction(), u.direction() - Angle::degrees(90)));
        xassert(fcmp(v.magnitude(), 5));

        w = u;
        w.rotate(Angle::degrees(-90)).translate(u.head());
        xassert(w.tail() == v.tail());
        xassert(w.head() == v.head());
        xassert(fcmp(w.direction(), v.direction()));
        xassert(fcmp(w.magnitude(), v.magnitude()));
    }

    xassert(Vector(Point(3, 4)).description() == std::string("Vector (0, 0), (3, 4); 0.927295 (53.1301°), 5"));
}

#endif
