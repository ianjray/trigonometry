# trigonometry
C++ trigonometry

## Examples

```c
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
```
