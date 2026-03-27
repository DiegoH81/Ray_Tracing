#ifndef HITTABLE_H
#define HITTABLE_H

#include "RTH.h"

class Material;

class HitRecord
{
public:
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> material;
	double t;
	bool front_face;

	HitRecord() :
		point(), normal(), t(-1.0), front_face(false)
	{}

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

	virtual bool hit(const Ray& in_ray, Interval in_interval, HitRecord& in_record) = 0;
};

#endif