#ifndef Pixel_H
#define Pixel_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "DE1SoCfpga.h"
using namespace std;

//Header file that draws pixels and lines
class Pixel: public DE1SoCfpga { 
  public:
      void draw_Pixel(int x, int y,int color);
      void draw_Line(float x1, float y1, float x2, float y2, int color);

};

#endif

