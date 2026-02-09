#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
public:
	Ray():
		m_vector(), m_origin()
	{ }

	Ray(const Vec3& in_origin, const Point3& in_direction) :
		m_vector(in_direction), m_origin(in_origin) {}

	const Point3& origin() const { return m_origin; };
	const Point3& direction() const { return m_vector; };


	Point3 at(const double& in_distance) const
	{
		return m_origin + m_vector * in_distance;
	}
private:
	Vec3 m_vector;
	Point3 m_origin;
};

#endif
