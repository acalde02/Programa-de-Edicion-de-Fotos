#include "Pixel.h"


Pixel::Pixel()
{
    r = 0;
    g = 0;
    b = 0;
}


Pixel::Pixel(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

int Pixel::getR()
{
    return r;
}

int Pixel::getG()
{
    return g;
}

int Pixel::getB()
{
    return b;
}


int Pixel::toPackedRGB()
{
    return (r << 16) | (g << 8) | b;
}