#include "fcmp.hpp"
#include "equilateraltriangle.hpp"
#include "isoscelestriangle.hpp"
#include "rightangledtriangle.hpp"
#include "triangle.hpp"
#include "vector.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>

int main()
{
    {
        //   |     .
        //   |    /|\      .
        //   | a / | \ b   .
        //   |  /  |  \    .
        //   | /   |   \   .
        //   |/B  "|   A\  .
        // --+-----+-----+--
        //   |     c

        auto t = Triangle(5, 5, 8);

        assert(fcmp(t.A(), Angle::degrees(36.87)));
        assert(fcmp(t.B(), Angle::degrees(36.87)));
        assert(fcmp(t.C(), Angle::degrees(180 - t.A().deg() - t.B().deg())));
    }

    {
        //   |     .
        //   |    /|
        //   |   / |
        //   |  /  | opp (a)
        //   | /   |
        //   |/A  "|
        // --+-----+--
        //   | adj (b)

        auto t = RightAngledTriangle::with_a_b(3, 4);

        assert(fcmp(t.A(), Angle::degrees(36.87)));
        assert(fcmp(t.B(), Angle::degrees(53.13)));

        //   |     . (4,3)
        //   |    /
        //   |   /
        //   |  /
        //   | /
        //   |/
        // --+--------
        //   |

        auto v = Vector(t.A(), t.c());

        assert(v.tail() == Point());
        assert(fcmp(v.head().x(), t.b()));
        assert(fcmp(v.head().y(), t.a()));
    }

    {
        auto u = Vector{Point{3, 4}};
        assert(u.tail() == Point());
        assert(u.head() == Point(3, 4));

        auto v = Vector{Point{4, 3}};
        assert(v.tail() == Point());
        assert(v.head() == Point(4, 3));

        // Goal: Calculate direction and magnitude of XY.
        //
        // (3,4) X---+
        //       |\  |      XY = 1.414 = sqrt(1^2 + 1^2)
        //       | Z |      ZY = 0.707
        //       |  \|
        //       +---Y (4,3)
        //          /|
        //         / |
        //      v /  |
        //       /   |
        //      /    |
        //     /A   "|
        //    O------+
        //
        // Calculate angle B (in triangle formed by O,Y,Z) using 'a' ZY and 'c' OY.
        //
        //        O
        //       /|
        //      /A|
        //   c /  |
        //    /   | b
        //   /B  "|
        //  Y-----Z
        //     a
        //
        // Create vector w, rotated by the outside angle (180° - B) and translated to the head of v.

        auto XY = RightAngledTriangle::with_a_b(1, 1).c();
        assert(fcmp(XY, 1.414));

        auto ZY = XY / 2;

        auto OY = v.magnitude();

        auto B = RightAngledTriangle::with_a_c(ZY, OY).B();

        auto w = Vector{Angle::radians(M_PI - B), XY}.rotate(v.direction()).translate(v.head());
        assert(fcmp(w.direction(), Angle::degrees(135)));
        assert(fcmp(w.magnitude(), XY));
        assert(w.tail() == v.head());
        assert(w.head() == u.head());
    }

    {
        // https://twitter.com/engineers_feed/status/1687770310743932928?s=46&t=rs0qnL4wEDQO4-I2bpTiGA
        //
        //  A=20
        //  |\      .
        //  | \     .
        //  |  \    .
        //  |  /\   .
        //  | /D \  .
        //  |/    \ .
        //  +------+
        //  B      C=80
        //
        // Length AD == BC
        // Solve for the angle D using only elementary geometry.

        auto ABC = IsoscelesTriangle(Angle::degrees(20), 1);

        // Draw equilateral triangle ABE.

        auto ABE = EquilateralTriangle(ABC.side());

        // Draw isosceles triangle ACE.

        auto ACE = IsoscelesTriangle(ABE.angle() - ABC.vertexAngle(), ABE.side());

        assert(fcmp(ACE.vertexAngle(), Angle::degrees(40)));
        assert(fcmp(ACE.baseAngle(), Angle::degrees(70)));

        // The triangle formed by points BCE is a rotated version of ADB.

        auto BCE_E = ACE.baseAngle() - ABE.angle();
        assert(fcmp(BCE_E, Angle::degrees(10)));

        auto BCE_B = Angle::degrees(180) - BCE_E - ACE.baseAngle() - ABC.baseAngle();
        assert(fcmp(BCE_B, Angle::degrees(20)));

        auto ADB_B = BCE_E;
        auto BCD_B = ABC.baseAngle() - ADB_B;
        assert(fcmp(BCD_B, Angle::degrees(70)));

        // With BCE solved, we can now find angle D.

        auto BCD_D = Angle::degrees(180) - ABC.baseAngle() - BCD_B;
        assert(fcmp(BCD_D, Angle::degrees(30)));
    }
}
