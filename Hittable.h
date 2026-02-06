#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord
{
public:
	Point3 point;
	Vec3 normal;
	double t;
	bool front_face;

	void set_face_normal(const Ray& in_ray, const Vec3& outward_normal)
	{
		front_face = dot(in_ray.direction(), outward_normal) < 0;

		normal = front_face ? outward_normal : -1*outward_normal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& in_ray, double t_min, double t_max, HitRecord& in_record) = 0;
};

#endif