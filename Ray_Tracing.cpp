#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"

int main()
{
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
            auto pixel_color = color(double(i) / double(height), double(j) / double(width), 0.0);
            write_color(file, pixel_color);
        }
    }
}