#include "fcmp.h"
#include "rightangledtriangle.h"
#include "triangle.h"
#include "vector.h"
#include <cassert>
#include <cmath>
#include <cstdio>


//@unittest clang++ -std=c++17 -Wall angle.cpp fcmp.cpp point.cpp rightangledtriangle.cpp triangle.cpp vector.cpp
int main()
{
    {
        //   |     .
        //   |    /|\
        //   | a / | \ b
        //   |  /  |  \
        //   | /   |   \
        //   |/B  "|   A\
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
        //        /  |
        //       /   |
        //      /A  "|
        //     O-----+
        //
        // Calculate B using edges ZY and OY.
        //
        // (3,4) Z-----Y
        //        \"  B|
        //         \   |
        //          \  |
        //           \ |
        //            \|
        //             O
        //
        // Create vector w, rotated by the outside angle (180° - B) and translated to the head of v.

        auto OY = u.magnitude();

        auto XY = RightAngledTriangle::with_a_b(1, 1).c();
        assert(fcmp(XY, 1.414));

        auto ZY = XY / 2;

        auto B = RightAngledTriangle::with_a_c(ZY, OY).B();

        auto w = Vector{Angle::radians(M_PI - B), XY}.rotate(v.direction()).translate(v.head());
        assert(fcmp(w.direction(), Angle::degrees(135)));
        assert(fcmp(w.magnitude(), XY));
        assert(w.tail() == v.head());
        assert(w.head() == u.head());
    }
}
