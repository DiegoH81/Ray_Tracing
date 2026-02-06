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

};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& in_ray, double t_min, double t_max, HitRecord& in_record) = 0;
};

#endif