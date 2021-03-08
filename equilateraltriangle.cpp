#include "equilateraltriangle.hpp"

#include <cmath>
#include <sstream>

EquilateralTriangle::EquilateralTriangle(double side) : side_{side}
{
}

Angle EquilateralTriangle::angle() const
{
    return Angle::degrees(60);
}

double EquilateralTriangle::side() const
{
    return side_;
}

double EquilateralTriangle::height() const
{
    // Given Pythagoras theorem: Hypotenuse² = Base² + Height²
    // Then a² = (a/2)² + h²
    // Then h² = a² - (a/2)²
    // Then h² = (3a²)/4
    // Or   h  = (a√3)/2
    return side_ * sqrt(3) / 2;
}

std::string EquilateralTriangle::description() const
{
    std::stringstream ss;
    ss << "EquilateralTriangle "
        << side() << "; "
        << angle() << " (" << angle().deg() << "°)";
    return ss.str();
}

#ifdef UNITTEST_EQUILATERALTRIANGLE

#include "fcmp.hpp"
#include "rightangledtriangle.hpp"

#include "xassert.hpp"

int main()
{
    auto t = EquilateralTriangle(8);
    xassert(fcmp(t.angle(), Angle::degrees(60)));
    xassert(fcmp(t.side(), 8.00));
    xassert(fcmp(t.height(), 6.928));

    auto r = RightAngledTriangle::with_A_c(t.angle() / 2., t.side());
    xassert(fcmp(t.height(), r.b()));

    xassert(t.description() == "EquilateralTriangle 8; 1.0472 (60°)");
}

#endif
