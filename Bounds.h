#ifndef Bounds_H
#define Bounds_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "DE1SoCfpga.h"
#include "Pixel.h"
using namespace std;

//Header file
class Bounds: public Pixel {  
  private:
          
  public:
      Bounds();
      double *v;
      int count;
      int size;
      int Distance(double x1, double y1, double x2, double y2);
      void findBounds(int num_vertices, int *vertices, int &center_x, int &center_y, int &radius, int &quad);
      struct Point
      {
      double x;
      double y;
      };
      
  
      
      
      

};

#endif