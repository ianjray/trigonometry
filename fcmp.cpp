#include "fcmp.hpp"

#include <cmath>

bool fcmp(double x, double y, int precision)
{
    auto scale = pow(10, precision);
    return round(x * scale) == round(y * scale);
}

#ifdef UNITTEST_FCMP

#include "xassert.hpp"

int main()
{
    xassert(!fcmp(5.11, 5.12, 2));

    xassert( fcmp(3.9999946407, 4, 4));

    xassert(!fcmp(3.1415926535, 2, 0));
    xassert( fcmp(3.1415926535, 3, 0));
    xassert(!fcmp(3.1415926535, 4, 0));

    xassert(!fcmp(3.1415926535, 3.0,  1));
    xassert( fcmp(3.1415926535, 3.1,  1));
    xassert(!fcmp(3.1415926535, 3.2,  1));

    xassert(!fcmp(3.1415926535, 3.14159264, 8));
    xassert( fcmp(3.1415926535, 3.14159265, 8));
    xassert(!fcmp(3.1415926535, 3.14159266, 8));
}

#endif
