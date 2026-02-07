#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "RTH.h"
#include "Hittable.h"
#include <vector>

class HittableList : public Hittable
{
public:
	std::vector<std::shared_ptr<Hittable>> objects;


	HittableList(): objects() {}
	HittableList(std::shared_ptr<Hittable> in_obj)
	{
		add(in_obj);
	}

	void add(std::shared_ptr<Hittable> in_obj)
	{
		objects.push_back(in_obj);
	}

	void clear()
	{
		objects.clear();
	}

	bool hit(const Ray& in_ray, Interval in_interval, HitRecord& in_record) override
	{
		HitRecord temp_rec;
		bool hit_anything{ false };
		double closest_so_far = in_interval.max;

		for (auto& object : objects)
		{
			if (object->hit(in_ray, Interval(in_interval.min, closest_so_far), temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				in_record = temp_rec;
			}
		}

		return hit_anything;
	}
};


#endif