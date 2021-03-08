#include "isoscelestriangle.hpp"

#include "angle.hpp"
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

IsoscelesTriangle::IsoscelesTriangle(const Angle & V, double side) : V_{V}, side_{side}
{
}

Angle IsoscelesTriangle::vertexAngle() const
{
    return V_;
}

Angle IsoscelesTriangle::baseAngle() const
{
    //       V
    //       +
    //      / \    .
    //     /   \   .
    //    /     \  .
    //   /       \ .
    //  +----+----+
    //  B         B

    // 180° total
    return Angle::radians((Angle::degrees(180) - V_) / 2.);
}

double IsoscelesTriangle::side() const
{
    return side_;
}

double IsoscelesTriangle::base() const
{
    //       A
    //       +
    //       |\     .
    //       | \    .
    //       |  \ c .
    //       |   \  .
    //       +----+
    //         a

    auto r = RightAngledTriangle::with_A_c(V_ / 2., side());
    return r.a() * 2;
}

double IsoscelesTriangle::height() const
{
    // Given Pythagoras theorem: Hypotenuse² = Base² + Height²
    // Then h² = side² - (base/2)²
    // Or   h  = √(side² - (base/2)²)
    return sqrt(sqr(side()) - sqr(base() / 2));
}

std::string IsoscelesTriangle::description() const
{
    std::stringstream ss;
    ss << "IsoscelesTriangle "
        << side() << ", " << base() << "; "
        << vertexAngle() << " (" << vertexAngle().deg() << "°), "
        << baseAngle() << " (" << baseAngle().deg() << "°)";
    return ss.str();
}

#ifdef UNITTEST_ISOSCELESTRIANGLE

#include "fcmp.h"

#include <cassert>

int main()
{
    {
        auto t = IsoscelesTriangle(Angle::degrees(40), 5);
        assert(fcmp(t.vertexAngle(), Angle::degrees(40)));
        assert(fcmp(t.baseAngle(), Angle::degrees(70)));
        assert(fcmp(t.side(), 5.00));
        assert(fcmp(t.base(), 3.42));

        auto r = RightAngledTriangle::with_A_c(t.vertexAngle() / 2., t.side());
        assert(fcmp(t.height(), r.b()));
        assert(fcmp(t.height(), 4.698));
    }

    {
        // Isosceles triangle comprised of two 3-4-5 triangles.
        auto t = IsoscelesTriangle(Angle::degrees(106.26), 5);
        assert(fcmp(t.baseAngle(), Angle::degrees(36.87)));
        assert(fcmp(t.side(), 5));
        assert(fcmp(t.base(), 8));
        assert(fcmp(t.height(), 3));

        assert(t.description() == "IsoscelesTriangle 5, 7.99999; 1.85459 (106.26°), 0.643503 (36.87°)");
    }
}

#endif
