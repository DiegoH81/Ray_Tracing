#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
	Sphere(const Point3& in_center, const double& in_radius) :
		m_center(in_center), m_radius(std::fmax(0.0, in_radius)) {}

	bool hit(const Ray& in_ray, double t_min, double t_max, HitRecord& in_record) override
	{
		auto r_c = m_center - in_ray.origin();

		auto a = dot(in_ray.direction(), in_ray.direction());
		auto h = dot(in_ray.direction(), r_c);
		auto c = dot(r_c, r_c) - (m_radius * m_radius);

		auto discriminant = h * h - a * c;
		if (discriminant < 0.0)
			return false;

		auto sqrt_d = std::sqrt(discriminant);


		auto root = (h - sqrt_d) / a;
		if (root <= t_min || root >= t_max)
		{
			root = (h + sqrt_d) / a;
			if (root <= t_min || root >= t_max)
				return false;
		}

		in_record.t = root;
		in_record.point = in_ray.at(root);
		Vec3 outward_normal_unit = (in_record.point - m_center) / m_radius;

		in_record.set_face_normal(in_ray, outward_normal_unit);


		return true;
	}

private:
	Point3 m_center;
	double m_radius;
};
#endif