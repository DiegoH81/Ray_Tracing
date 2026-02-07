#ifndef RTHEADER_H
#define RTHEADER_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

#include "Color.h"
#include "Ray.h"
#include "Vec3.h"
#include "Interval.h"

#endif