#include <iostream>
#include <string>
#include <fstream>

static const int width = 256;
static const int height = 256;
int size = width * height;

int *r = new int[size];
int *g = new int[size];
int *b = new int[size];

void SetPixel(int x, int y, int ColorR, int ColorG, int ColorB)
{
    int index = x + y * width;
    r[index] = ColorR;
    g[index] = ColorG;
    b[index] = ColorB;
}

bool Render(std::string filename)
{
    std::ofstream f(filename);
    if (!f)
    {
        std::cerr << "Error: Cannot open file for writing." << std::endl;
        return false;
    }

    f << "P3\n"
      << width << ' ' << height << "\n255\n";
    for (int i = 0; i < size; ++i)
    {
        f << r[i] << ' ' << g[i] << ' ' << b[i] << ' ';
    }
    f << '\n';

    std::cout << "PPM image written to output.ppm" << std::endl;
    return true;
}

void DrawLine(int x1, int y1, int xn, int yn, int r, int g, int b)
{
    double k = 1.0 * (yn - y1) / (xn - x1);
    int xi = x1;
    int yi = y1;
    double delta = 0;
    SetPixel(x1, y1, r, g, b);
    while (xi != xn)
    {
        xi += 1;
        delta += k;
        if (delta >= 0.5) // 直接比较delta与0.5
        {
            yi += 1;
            delta -= 1.0; // 更新delta，而非middle
        }
        SetPixel(xi, yi, r, g, b);
    }
}
int main()
{

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            SetPixel(x, y, 255, 255, 255);
        }
    }
    DrawLine(10, 10, 200, 100, 0, 0, 0);
    Render("output.ppm");

    delete[] r;
    delete[] g;
    delete[] b;
    return 0;
}