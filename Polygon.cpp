#include "Polygon.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <math.h>
using namespace std;

#define BLUE 0x187F


//Want to initialize Number of points and also coordinates of points
Polygon::Polygon(int number_of_points, int *coordinates, int dx_in, int dy_in) 
{
  size = number_of_points * 2;
  num_vertices = number_of_points;
  vertices = new int[size];
  
  //Copy over data
  for (int i = 0; i < size; i++){
    vertices[i] = coordinates[i];
  }
  
  dx = dx_in;
  dy = dy_in;
  
  //drawPolygon(); We dont want to draw the Polygon until we figure 
}

Polygon::~Polygon()
{
  erasePolygon();
}


void Polygon::drawPolygon()
{
  int i;

  for(i=0;i<num_vertices-1;i++)
  {
    draw_Line(vertices[(i<<1)+0],
         vertices[(i<<1)+1],
         vertices[(i<<1)+2],
         vertices[(i<<1)+3], 
         BLUE);
  }
  draw_Line(vertices[0],
       vertices[1],
       vertices[(num_vertices<<1)-2],
       vertices[(num_vertices<<1)-1], 
       BLUE);
  
  //Everytime drawPolygon() is called, we will need to remake the Bounds/Circle Bounding
  findBounds(num_vertices, vertices, center_x, center_y, radius, quad);
  
}

void Polygon::erasePolygon()
{
  int i;

  for(i=0;i<num_vertices-1;i++)
  {
    draw_Line(vertices[(i<<1)+0],
         vertices[(i<<1)+1],
         vertices[(i<<1)+2],
         vertices[(i<<1)+3], 0
         );
  }
  draw_Line(vertices[0],
       vertices[1],
       vertices[(num_vertices<<1)-2],
       vertices[(num_vertices<<1)-1], 0
       );
}

//Will Scale Polygons
void Polygon::Scaling(double factor)
{
  int x,y;
  erasePolygon();
  
  for (int i=0; i<size; i = i+2){
    x = vertices[i] - center_x;
    y = vertices[i+1] - center_y;
    
    vertices[i] = x;
    vertices[i+1] = y;
  }
  
  
  for (int i=0; i<size; i = i+2){
    x = vertices[i];
    y = vertices[i+1];
    
    int scaled_x = int(x * factor);
    int scaled_y = int(y * factor);
    
    vertices[i] = scaled_x;
    vertices[i+1] = scaled_y;
  }
  
  for (int i=0; i<size; i = i+2){
    x = vertices[i] + center_x;
    y = vertices[i+1] + center_y;
    
    vertices[i] = x;
    vertices[i+1] = y;
  }

  drawPolygon();
}

//Rotate() assumes array is in clockwise order
void Polygon::Rotate()
{
  double degrees = 90;
  double pi = 3.14159265359;
  int rotated_x, rotated_y;
  
  double radians =  degrees * (pi/180);
  double c = cos(radians);
  double s = sin(radians);
  c = int(c);
  s = int(s);
  
  int x;
  int y;
  
  erasePolygon();
  
  for (int i=0; i<size; i = i+2){
    x = vertices[i] - center_x;
    y = vertices[i+1] - center_y;
    
    vertices[i] = x;
    vertices[i+1] = y;
  }
  
  
  for (int i=0; i<size; i = i+2){
    x = vertices[i];
    y = vertices[i+1];
    rotated_x = (x * c) - (y * s);
    rotated_y = (x * s) + (y * c);
    
    vertices[i] = rotated_x;
    vertices[i+1] = rotated_y;
  }
  
  for (int i=0; i<size; i = i+2){
    x = vertices[i] + center_x;
    y = vertices[i+1] + center_y;
    
    vertices[i] = x;
    vertices[i+1] = y;
  }
  
  drawPolygon();
  
  
}

void Polygon::checkCollision(Polygon *polygon)
{
  if(this->quad == polygon->quad){
    int sum_rad = (this->radius) + (polygon->radius);
    
    int d = Distance(this->center_x, this->center_y, polygon->center_x, polygon->center_y);
    
    int slope;
    int change_x = (this->center_x) - (polygon->center_x);
    int change_y = (this->center_y) - (polygon->center_y);
    
    if(change_x != 0){
      slope = change_y / change_x;
    }
    
    //Check for floating point exception -- change_x is 0
  
    
    if(d <= sum_rad){
      if(dx == 0 && polygon->dx == 0){
        dy = -dy;
        polygon->dy = -dy;
      }else if(slope == 0){ //Horizontal line
        dx = -dx;
        polygon->dx = -dx;
      }else{
          dx = -dx;
          dy = -dy;
          polygon->dx = -dx;
          polygon->dy = -dy;
      }
    }
  }
}

void Polygon::checkMonitor()
{
  
  //Check collision with monitor
  int check_plusx = this->center_x + (radius);
  int check_minusx = this->center_x - (radius);
  int check_plusy = this->center_y + (radius);
  int check_minusy = this->center_y - (radius);
  //Check top and bottom part of screen
  if(check_minusy < 0){
    dy = -dy;
  }
  if(check_plusy > 239){
    dy = -dy;
  }
  //Check sides
  if(check_minusx < 0){
    dx = -dx;
  }
  if(check_plusx > 319){
    dx = -dx;
  }
}
  
  
    
    
  
  
  /*
    Will also give new direction of object
    if(dx == 0 && dy < 0){ //Moving up
      if(polygon.dx == 0 && polygon.dy > 0){ //Other Object moving down
        dy = -dy;
        polygon->dy = -dy;
      }
      else if(polygon.dx > 0 && polygon.dy == 0){ //Other Object moving right
        dx = polygon.dx;
        polygon.dx = 
      }
      else if(polygon.dx < 0 && polygon.dy == 0){ //Other Object moving left
      }
    }else if(dx == 0 && dy > 0 ){ // Moving Down
      
    }else if(dx < 0 && dy == 0) { // Moving Left
    }else if(dx > 0 && dy == 0){ // Moving right
    }
  }
  
    
  
    if(dx > 0 && dy == 0){ // Moving right
      if(polygon->dx < 0 && polygon->dy == 0){
        dx = -dx;
        polygon->dx = -dx;
        cout << "Collision Detected" << endl;
      }
    }else if(dx < 0 && dy == 0){
      if(polygon->dx > 0 && polygon->dy == 0){
        dx = -dx;
        polygon->dx = -dx;
        cout << "Wat" << endl;
      }
    }
      
  
  }
  */


void Polygon::Move()
{
  //Want to calculate new x and y coorindates based on dx, dy
  erasePolygon();
  
  for(int i=0;i<size;i = i + 2)  {
    vertices[i] = vertices[i] + dx;
  }
  
  for(int i=1;i<size;i = i + 2)  {
    vertices[i] = vertices[i] + dy;
  }
  
  drawPolygon();
  
}

void Polygon::shiftRight()
{
  erasePolygon();
  //Loop only shifts x-values right
  for(int i=0;i<size;i = i + 2)  {
    vertices[i] = vertices[i] + 50;
  }
  drawPolygon();
}

void Polygon::shiftLeft()
{
  erasePolygon();
  //Loop only shifts x-values left
  for(int i=0;i<size;i = i + 2)  {
    vertices[i] = vertices[i] - 50;
  }
  drawPolygon();
}

void Polygon::shiftUp()
{
  erasePolygon();
  //Loop only shifts y-values down
  for(int i=1;i<size;i = i + 2)  {
    vertices[i] = vertices[i] - 50;
  }
  drawPolygon();
}

void Polygon::shiftDown()
{
  erasePolygon();
  //Loop only shifts x-values down
  for(int i=1;i<size;i = i + 2)  {
    vertices[i] = vertices[i] + 50;
  }
  drawPolygon();
}


