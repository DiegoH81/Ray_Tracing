#ifndef MATERIAL_H
#define MATERIAL_H

#include "RTH.h"
#include "Hittable.h"

class Material
{
public:

	virtual bool scatter(const Ray& in_ray, HitRecord& in_record, color& attenuation, Ray& scatter_ray)
	{
		return false;
	}
};


class Lambertian: public Material
{
public:

	Lambertian(const color& in_color) :
		albedo(in_color) {}


	bool scatter(const Ray& in_ray, HitRecord& in_hit, color& attenuation, Ray& scatter_ray) override
	{
		auto scatter_dir = in_hit.normal + random_unit_vector();
		if (scatter_dir.near_zero())
			scatter_dir = in_hit.normal;


		attenuation = albedo;
		scatter_ray = Ray(in_hit.point, scatter_dir);
		return true;
	}


	color albedo;
};

class Metal : public Material
{
public:

	Metal(const color& in_color) :
		albedo(in_color) {
	}


	bool scatter(const Ray& in_ray, HitRecord& in_hit, color& attenuation, Ray& scatter_ray) override
	{
		auto scatter_dir = reflect(in_ray.direction(), in_hit.normal);

		attenuation = albedo;
		scatter_ray = Ray(in_hit.point, scatter_dir);
		return true;
	}

	color albedo;
};


#endif