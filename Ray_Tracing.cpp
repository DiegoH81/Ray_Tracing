#include "RTH.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

int main()
{
    // World
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    Camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.focal_length = 1.0;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world, "graph.ppm");
}