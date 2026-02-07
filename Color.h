#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "Interval.h"

#include <cmath>
#include <iostream>

using color = Vec3;

inline void write_color(std::ostream& out, const color in_pixel_color)
{
	auto& r = in_pixel_color.x;
	auto& g = in_pixel_color.y;
	auto& b = in_pixel_color.z;

	
	Interval valid_range(0.000, 0.999);
	double out_r = 255.9 * valid_range.clamp(r);
	double out_g = 255.9 * valid_range.clamp(g);
	double out_b = 255.9 * valid_range.clamp(b);

	out << out_r << " " << out_g << " " << out_b << "\n";
}

#endif