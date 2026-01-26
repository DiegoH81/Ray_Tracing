#pragma once
#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <iostream>
#include "Vec3.h"

using color = Vec3;

void write_color(std::ostream& out, const color in_pixel_color)
{
	auto& r = in_pixel_color.x;
	auto& g = in_pixel_color.y;
	auto& b = in_pixel_color.z;

	double out_r = 255.9 * r;
	double out_g = 255.9 * g;
	double out_b = 255.9 * b;

	out << out_r << " " << out_g << " " << out_b << "\n";
}

#endif