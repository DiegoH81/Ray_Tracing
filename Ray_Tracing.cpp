#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

bool hit_sphere(const Point3& in_center, double radius, Ray& in_ray)
{

    auto r_c = in_center - in_ray.origin();

    auto a = dot(in_ray.direction(), in_ray.direction());
    auto b = 2 * (dot(in_ray.direction(), r_c));
    auto c = dot(r_c, r_c) - (radius * radius);

    auto discriminant = b * b - 4 * a * c;

    return (discriminant >= 0);
}

color ray_color(Ray& in_ray)
{
    if (hit_sphere(Point3(-1, 0, -1), 0.4, in_ray))
        return color(1.0, 0.0, 1.0);  // Red color

    Vec3 unit_ray_direction = unit(in_ray.direction());
    double a = 0.5 * (unit_ray_direction.y + 1.0);

    color new_color = (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);

    return new_color;
}


int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1 ? 1 : image_height);


    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width) / double(image_height));


    double focal_length = 1.0;

    Point3 camera_center = Point3(0, 0, 0);
    Vec3 vector_u = Vec3(viewport_width, 0, 0);
    Vec3 vector_v = Vec3(0, -viewport_height, 0);

    Vec3 pixel_delta_u = vector_u / image_width;
    Vec3 pixel_delta_v = vector_v / image_height;

    Point3 viewport_top_left = camera_center - Vec3(0, 0, focal_length) - vector_u / 2 - vector_v / 2;
    Point3 pixel_00 = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    std::cout << "Image width: " << image_width << " Image height: " << image_height << "\n";

    std::ofstream file("graph.ppm", std::ios::out);

    file << "P3\n";
    file << image_width << " " << image_height<< "\n";
    file << "255\n";

    for (int i = 0; i < image_height; i++)
    {
        std::clog << "Lines remaining: " << image_height - i << "\n";
        for (int j = 0; j < image_width; j++)
        {
            auto pixel_center = pixel_00 + (pixel_delta_u * j) + (pixel_delta_v * i);
            auto ray_direction = pixel_center - camera_center;

            auto ray = Ray(camera_center, ray_direction);

            auto pixel_color = ray_color(ray);
            write_color(file, pixel_color);
        }
    }
}