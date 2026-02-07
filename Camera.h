#ifndef CAMERA_H
#define CAMERA_H

#include "RTH.h"
#include "HittableList.h"
#include "Color.h"

#include <fstream>

class Camera
{
public:
    int image_width;
    int samples_per_pixel;
    double viewport_height, aspect_ratio, focal_length;

    Camera():
        image_width(100), viewport_height(2.0), aspect_ratio(1.0), focal_length(1.0),
        samples_per_pixel(10),
        image_height(-1), camera_center(), pixel_00(), pixel_delta_u(), pixel_delta_v(),
        pixel_sample_scale(-1.0)
    {}

    void render(HittableList& world, const std::string& filename)
    {
        initialize();

        std::cout << "Image width: " << image_width << " Image height: " << image_height << "\n";

        std::ofstream file(filename, std::ios::out);

        file << "P3\n";
        file << image_width << " " << image_height << "\n";
        file << "255\n";

        for (int i = 0; i < image_height; i++)
        {
            std::clog << "Lines remaining: " << image_height - i << "\n";
            for (int j = 0; j < image_width; j++)
            {
                color pixel_color(0.0, 0.0, 0.0);

                for (int n = 0; n < samples_per_pixel; n++)
                {
                    auto r = get_ray(j, i);
                    pixel_color += ray_color(r, world);
                }
                write_color(file, pixel_color * pixel_sample_scale);
            }
        }
    }
private:
    int image_height;
    double pixel_sample_scale;
    Point3 camera_center, pixel_00;
    Vec3 pixel_delta_u, pixel_delta_v;

    void initialize()
    {
        pixel_sample_scale = 1.0 / double(samples_per_pixel);

        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1 ? 1 : image_height);


        double viewport_width = viewport_height * (double(image_width) / double(image_height));

        // Camera
        Vec3 vector_u, vector_v;
        camera_center = Point3(0, 0, 0);
        vector_u = Vec3(viewport_width, 0, 0);
        vector_v = Vec3(0, -viewport_height, 0);

        pixel_delta_u = vector_u / image_width;
        pixel_delta_v = vector_v / image_height;

        Point3 viewport_top_left = camera_center - Vec3(0, 0, focal_length) - vector_u / 2 - vector_v / 2;
        pixel_00 = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(Ray& in_ray, Hittable& world)
    {
        HitRecord rec;
        if (world.hit(in_ray, Interval(0, infinity), rec))
        {
            //std::cout << "HITTT\n";
            return 0.5 * (rec.normal + color(1.0, 1.0, 1.0));
        }

        // Background
        Vec3 unit_ray_direction = unit(in_ray.direction());
        double a = 0.5 * (unit_ray_direction.y + 1.0);

        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);;
    }

    Ray get_ray(int in_x, int in_y)
    {
        auto offset = sample_square();
        auto pixel_sample = pixel_00 + ((offset.x + in_x) * pixel_delta_u) +
                                       ((offset.y + in_y) * pixel_delta_v);
        

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);

    }

    Vec3 sample_square()
    {
        return Vec3(random_double() - 0.5, random_double() - 0.5, 0.0);
    }
};

#endif