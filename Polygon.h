#ifndef Polygon_H
#define Polygon_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "DE1SoCfpga.h"
#include "Pixel.h"
#include "Bounds.h"
using namespace std;

//Header file that draws pixels,lines, and polygons
class Polygon: public Bounds {  
  public:
      int num_vertices;
      int *vertices;
      int size;
      int radius;
      int center_x;
      int center_y;
      int quad;
      //+ dx is right -dx is left
      int dx;
      //+ dy is down -dy is up
      int dy;
      Polygon(int number_of_points, int *coordinates,int dx_in, int dy_in);
      ~Polygon();
      void drawPolygon();
      void erasePolygon();
      void Scaling(double factor);
      void Rotate();
      void checkCollision(Polygon *polygon);
      void checkMonitor();
      void Move();
      void shiftRight();
      void shiftLeft();
      void shiftUp();
      void shiftDown();

};

#endif

