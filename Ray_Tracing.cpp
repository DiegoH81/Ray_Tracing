#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("graph.ppm", std::ios::out);
    int width{ 256 }, height{ 256 };


    std::cout << "start\n";
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";
    for (int i = 0; i < height; i++)
    {
        std::clog << "Lines remaining: " << height - i << "\n";
        for (int j = 0; j < width; j++)
        {
            double red = double(i) / double(width - 1);
            double green = double(j) / double(height - 1);

            int i_red = int(red * 255.999);
            int i_green = int(green * 255.999);
            int i_blue = 0;


            file << i_red << " " << i_green << " " << i_blue << "\n";
        }
    }
    std::cout << "end\n";
}