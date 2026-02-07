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
    double viewport_height, aspect_ratio, focal_length;

    Camera():
        image_width(100), viewport_height(2.0), aspect_ratio(1.0), focal_length(1.0),
        image_height(-1), camera_center(), pixel_00(), pixel_delta_u(), pixel_delta_v()
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
                auto pixel_center = pixel_00 + (pixel_delta_u * j) + (pixel_delta_v * i);
                auto ray_direction = pixel_center - camera_center;

                auto ray = Ray(camera_center, ray_direction);

                auto pixel_color = ray_color(ray, world);
                write_color(file, pixel_color);
            }
        }
    }
private:
    int image_height;
    Point3 camera_center, pixel_00;
    Vec3 pixel_delta_u, pixel_delta_v;

    void initialize()
    {
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
            return 0.5 * (rec.normal + color(1.0, 1.0, 1.0));

        // Background
        Vec3 unit_ray_direction = unit(in_ray.direction());
        double a = 0.5 * (unit_ray_direction.y + 1.0);

        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);;
    }
};

#endif