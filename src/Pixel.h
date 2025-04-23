# pragma once
# include <iostream>

using namespace std; 

class Pixel {
public:
    int r, g, b;
    Pixel();
    Pixel(int r, int g, int b);
    int getR(), getG(), getB();
    int toPackedRGB();
  };
  