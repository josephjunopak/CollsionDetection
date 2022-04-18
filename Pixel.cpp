#include "Pixel.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <math.h>
using namespace std;

void Pixel::draw_Pixel(int x, int y, int color){
  int pixel;
  int row = y;
  int col = x;
  
  pixel = 0 + (row << 10) + (col << 1);
  Draw(pixel, color);
  
}

void Pixel::draw_Line(float x1, float y1, float x2, float y2, int color)
{
  // Bresenham's line algorithm
  const bool steep = (abs(y2 - y1) > abs(x2 - x1));
  if(steep)
  {
    std::swap(x1, y1);
    std::swap(x2, y2);
  }
 
  if(x1 > x2)
  {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
 
  const float dx = x2 - x1;
  const float dy = abs(y2 - y1);
 
  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;
 
  const int maxX = (int)x2;
 
  for(int x=(int)x1; x<=maxX; x++)
  {
    if(steep)
    {
        draw_Pixel(y,x, color);
    }
    else
    {
        draw_Pixel(x,y, color);
    }
 
    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }
  }
}