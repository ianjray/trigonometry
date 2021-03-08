#include "triangle.hpp"

#include "rightangledtriangle.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>

namespace
{

/// @return @c x squared.
inline double sqr(double x)
{
    return pow(x, 2);
}

inline Angle C_from_a_b_c(double a, double b, double c)
{
    // Cosine rule:
    // c2 = a2 + b2 − 2ab cos(C)
    // Thus C = acos(a2 + b2 - c2 / 2ab)
    return Angle::radians(acos((sqr(a) + sqr(b) - sqr(c)) / (2 * a * b)));
}

/// @return double c^2
inline double cosine_rule(double a, double b, const Angle & C)
{
    // Cosine rule:
    // c2 = a2 + b2 − 2ab cos(C)
    return sqr(a) + sqr(b) - 2 * a * b * cos(C);
}

/// @return Length @c a.
inline double sine_rule(const Angle & A, double ratio)
{
    // Sine rule:
    // sin(A)/a = ratio = sin(B)/b = sin(C)/c
    return sin(A) / ratio;
}

/// @return Angle @c A.
inline Angle sine_rule(double a, double ratio)
{
    return Angle::radians(asin(ratio * a));
}

} // namespace

Triangle::Triangle(double a, double b, double c) : a_{a}, b_{b}, c_{c}
{
    C_ = C_from_a_b_c(a_, b_, c_);

    auto ratio = sin(C_) / c_;
    A_ = sine_rule(a_, ratio);

    // 180° total
    B_ = Angle::radians(Angle::degrees(180.) - A_ - C_);
}

Triangle Triangle::with_a_b_C(double a, double b, const Angle & C)
{
    return Triangle(a, b, sqrt(cosine_rule(a, b, C)));
}

Triangle Triangle::with_A_B_c(const Angle & A, const Angle & B, double c)
{
    // 180° total
    auto C = Angle::radians(Angle::degrees(180.) - A - B);
    auto ratio = sin(C) / c;
    auto a = sine_rule(A, ratio);
    auto b = sine_rule(B, ratio);
    return Triangle(a, b, c);
}

RightAngledTriangle Triangle::subA() const
{
    return RightAngledTriangle::with_A_c(A(), b());
}

RightAngledTriangle Triangle::subB() const
{
    return RightAngledTriangle::with_A_c(B(), a());
}

Angle Triangle::A() const
{
    return A_;
}

Angle Triangle::B() const
{
    return B_;
}

Angle Triangle::C() const
{
    return C_;
}

double Triangle::a() const
{
    return a_;
}

double Triangle::b() const
{
    return b_;
}

double Triangle::c() const
{
    return c_;
}

std::string Triangle::description() const
{
    std::stringstream ss;
    ss << "Triangle "
        << a() << ", "
        << b() << ", "
        << c() << "; "
        << A() << " (" << A().deg() << "°), "
        << B() << " (" << B().deg() << "°), "
        << C() << " (" << C().deg() << ")";
    return ss.str();
}

#ifdef UNITTEST_TRIANGLE

#include "fcmp.hpp"

#include "xassert.hpp"

int main()
{
    auto t = Triangle(23.41209, 30.098, 44.00033);
    xassert(fcmp(t.A(), Angle::degrees(30)));
    xassert(fcmp(t.B(), Angle::degrees(40)));
    xassert(fcmp(t.C(), Angle::degrees(110)));
    xassert(fcmp(t.a(), 23.41209));
    xassert(fcmp(t.b(), 30.098));
    xassert(fcmp(t.c(), 44.00033));

    t = Triangle::with_a_b_C(5, 5, Angle::degrees(106.26));
    xassert(fcmp(t.A(), Angle::degrees(36.87)));
    xassert(fcmp(t.B(), Angle::degrees(36.87)));
    xassert(fcmp(t.C(), Angle::degrees(106.26)));
    xassert(fcmp(t.a(), 5));
    xassert(fcmp(t.b(), 5));
    xassert(fcmp(t.c(), 8));

    t = Triangle::with_A_B_c(Angle::degrees(30), Angle::degrees(40), 50);
    xassert(fcmp(t.A(), Angle::degrees(30)));
    xassert(fcmp(t.B(), Angle::degrees(40)));
    xassert(fcmp(t.C(), Angle::degrees(110)));
    xassert(fcmp(t.a(), 26.604));
    xassert(fcmp(t.b(), 34.202));
    xassert(fcmp(t.c(), 50));

    auto m = t.subA();
    xassert(fcmp(m.A(), Angle::degrees(30)));
    xassert(fcmp(m.B(), Angle::degrees(60)));
    xassert(fcmp(m.a(), 17.101));
    xassert(fcmp(m.c(), 34.202));

    auto n = t.subB();
    xassert(fcmp(n.A(), Angle::degrees(40)));
    xassert(fcmp(n.B(), Angle::degrees(50)));
    xassert(fcmp(n.a(), 17.101));
    xassert(fcmp(n.c(), 26.604));

    xassert(fcmp(m.b() + n.b(), t.c()));

    xassert(Triangle::with_a_b_C(5, 5, Angle::degrees(106.26)).description() == std::string("Triangle 5, 5, 7.99999; 0.643503 (36.87°), 0.643503 (36.87°), 1.85459 (106.26)"));
}

#endif
