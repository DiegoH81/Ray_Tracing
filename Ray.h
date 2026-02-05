#pragma once
#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
public:
	Ray(const Vec3& in_vector, const Point3& in_origin) :
		m_vector(in_vector), m_origin(in_origin) {}

	const Point3& origin() { return m_origin; };
	const Point3& vector() { return m_vector; };


	Point3 at(const double& in_distance) const
	{
		return m_origin + m_vector * in_distance;
	}
private:
	Vec3 m_vector;
	Point3 m_origin;
};

#endif#pragma once
