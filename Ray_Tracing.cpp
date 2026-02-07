#include "RTH.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

int main()
{
    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100));

    // Camera
    Camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.focal_length = 1.0;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world, "graph.ppm");
}