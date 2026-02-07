#ifndef INTERVAL_H
#define INTERVAL_H

#include "RTH.h"

class Interval
{
public:
	double min, max;

	Interval() : min(+infinity), max(-infinity) {}
	Interval(double in_min, double in_max) : min(in_min), max(in_max) {}
	
	double size() const { return max - min; }

	bool contains(double in_x) { return min <= in_x && in_x <= max; }

	bool surrounds(double in_x) { return min < in_x && in_x < max; }

	static const Interval empty, universe;
};

inline const Interval Interval::empty = Interval(+infinity, -infinity);
inline const Interval Interval::universe = Interval(-infinity, +infinity);

#endif
