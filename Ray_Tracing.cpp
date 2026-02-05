#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

color ray_color(Ray in_ray)
{
    return color(0, 0, 0);
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

    Vec3 pixel_delta_u = vector_u / viewport_width;
    Vec3 pixel_delta_v = vector_v / viewport_height;

    Point3 viewport_top_left = camera_center - Vec3(0, 0, focal_length) - vector_u / 2 - vector_v / 2;
    Point3 pixel_00 = viewport_top_left + (vector_u + vector_v) * 0.5;


    std::cout << "Image width: " << image_width << " Image height: " << image_height << "\n";

    std::ofstream file("graph.ppm", std::ios::out);
    int width{ 256 }, height{ 256 };

    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";

    for (int i = 0; i < height; i++)
    {
        std::clog << "Lines remaining: " << height - i << "\n";
        for (int j = 0; j < width; j++)
        {
            auto pixel_center = pixel_00 + (vector_u * j) + (vector_v * i);
            auto ray_direction = camera_center - pixel_center;

            auto ray = Ray(pixel_center, ray_direction);

            auto pixel_color = ray_color(ray);
            write_color(file, pixel_color);
        }
    }
}