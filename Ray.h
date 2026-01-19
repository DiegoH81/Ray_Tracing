#pragma once
#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

using color = Vec3;

void write_color(std::ostream& out, color in_pixel_color)
{
	auto& r = in_pixel_color.x;
	auto& g = in_pixel_color.y;
	auto& b = in_pixel_color.z;

	double out_r = 255.9 * r;
	double out_g = 255.9 * g;
	double out_b = 255.9 * b;

	out << out_r << " " << out_g << " " << out_b << "\n";
}

#endif#pragma once
