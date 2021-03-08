#include "rightangledtriangle.hpp"

#include <cmath>
#include <sstream>

namespace
{

/// @return @c x squared.
inline double sqr(double x)
{
    return pow(x, 2);
}

} // namespace

RightAngledTriangle RightAngledTriangle::with_A_c(const Angle & A, double c)
{
    auto a = sin(A) * c;
    return with_a_c(a, c);
}

RightAngledTriangle RightAngledTriangle::with_a_b(double a, double b)
{
    auto a2 = sqr(a);
    auto b2 = sqr(b);
    auto c = sqrt(a2 + b2);
    return RightAngledTriangle(a, b, c);
}

RightAngledTriangle RightAngledTriangle::with_a_c(double a, double c)
{
    auto a2 = sqr(a);
    auto c2 = sqr(c);
    auto b = sqrt(c2 - a2);
    return RightAngledTriangle(a, b, c);
}

RightAngledTriangle RightAngledTriangle::with_a(const RightAngledTriangle & r, double a)
{
    auto b = a / tan(r.A());
    auto c = b / cos(r.A());
    return RightAngledTriangle(a, b, c);
}

RightAngledTriangle RightAngledTriangle::with_b(const RightAngledTriangle & r, double b)
{
    auto a = tan(r.A()) * b;
    auto c = b / cos(r.A());
    return RightAngledTriangle(a, b, c);
}

RightAngledTriangle RightAngledTriangle::with_c(const RightAngledTriangle & r, double c)
{
    auto a = sin(r.A()) * c;
    auto b = cos(r.A()) * c;
    return RightAngledTriangle(a, b, c);
}

RightAngledTriangle::RightAngledTriangle(double a, double b, double c) : a_{a}, b_{b}, c_{c}
{
    A_ = Angle::radians(atan(a / b));
}

Angle RightAngledTriangle::A() const
{
    return A_;
}

Angle RightAngledTriangle::B() const
{
    auto C_ = M_PI_2;
    return Angle::radians(M_PI - C_ - A());
}

double RightAngledTriangle::a() const
{
    return a_;
}

double RightAngledTriangle::b() const
{
    return b_;
}

double RightAngledTriangle::c() const
{
    return c_;
}

std::string RightAngledTriangle::description() const
{
    std::stringstream ss;
    ss << "RightAngledTriangle "
        << a() << ", " << b() << ", " << c() << "; "
        << A() << " (" << A().deg() << "°), "
        << B() << " (" << B().deg() << "°)";
    return ss.str();
}

#ifdef UNITTEST_RIGHTANGLEDTRIANGLE

#include "fcmp.hpp"

#include "xassert.hpp"

int main()
{
    auto t = RightAngledTriangle::with_a_b(1, sqrt(3));
    xassert(fcmp(t.A(), Angle::degrees(30)));
    xassert(fcmp(t.B(), Angle::degrees(60)));
    xassert(fcmp(t.a(), 1));
    xassert(fcmp(t.b(), sqrt(3)));
    xassert(fcmp(t.c(), 2));

    t = RightAngledTriangle::with_a_b(3, 4);
    xassert(fcmp(t.A(), Angle::degrees(36.87)));
    xassert(fcmp(t.B(), Angle::degrees(53.13)));
    xassert(fcmp(t.a(), 3));
    xassert(fcmp(t.b(), 4));
    xassert(fcmp(t.c(), 5));

    xassert(RightAngledTriangle::with_a_b(3, 4).description() == "RightAngledTriangle 3, 4, 5; 0.643501 (36.8699°), 0.927295 (53.1301°)");

    t = RightAngledTriangle::with_a_c(6, 10);
    xassert(fcmp(t.a(), 6));
    xassert(fcmp(t.b(), 8));
    xassert(fcmp(t.c(), 10));

    t = RightAngledTriangle::with_A_c(Angle::degrees(36.87), 5);
    xassert(fcmp(t.a(), 3));
    xassert(fcmp(t.b(), 4));
    xassert(fcmp(t.c(), 5));

    t = RightAngledTriangle::with_a(t, 30);
    xassert(fcmp(t.a(), 30));
    xassert(fcmp(t.b(), 40));
    xassert(fcmp(t.c(), 50));

    t = RightAngledTriangle::with_b(t, 80);
    xassert(fcmp(t.a(), 60));
    xassert(fcmp(t.b(), 80));
    xassert(fcmp(t.c(), 100));

    t = RightAngledTriangle::with_c(t, 10);
    xassert(fcmp(t.a(), 6));
    xassert(fcmp(t.b(), 8));
    xassert(fcmp(t.c(), 10));
}

#endif
