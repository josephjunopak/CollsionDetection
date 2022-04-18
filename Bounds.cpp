#include "Bounds.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <math.h>
using namespace std;

//Uses Smallest-Enclosing-Circle Algoritm to detect any collisions

#define BLUE 0x187F
#define PI 3.14

Bounds::Bounds() {
}


int Bounds::Distance(double x1, double y1, double x2, double y2){
  double d;
  double x = (x1 - x2)*(x1 - x2);
  double y = (y1 - y2)*(y1 - y2);
  d = x + y;
  d = sqrt(d);
  d = int(d);
  return d;
}



void Bounds::findBounds(int num_vertices, int *vertices, int &center_x, int &center_y, int &radius, int &quad) {
  //Create Circle
  Point p[num_vertices];
  int size = num_vertices * 2;
  int i,j;
  int add2 = 0;
  
  for(i=0;i<num_vertices;i++){
    p[i].x = vertices[add2];
    add2 = add2 + 2;
  }
  
  add2 = 1;
  
  for(i=0;i<num_vertices; i++){
    p[i].y = vertices[add2];
    add2 = add2 + 2;
  }
  
  int index1 = -1;
  int index2 = -1;
  int maxDistance = -1;
  
  for(i=0;i<num_vertices-1;i++){
        for(j=i+1;j<num_vertices;j++){

                int d = Distance(p[i].x,p[i].y,p[j].x,p[j].y);
                if(d>maxDistance){
                    maxDistance = d;
                    index1 = i;
                    index2 = j;


            }
        }
    }
    
    center_x = p[index1].x + p[index2].x;
    center_x = center_x /2 ;
    center_y = p[index1].y + p[index2].y;
    center_y = center_y / 2;
    radius = maxDistance/2;
    
    if(center_x > 0 && center_x < 160 && center_y > 0 && center_y < 120){
      quad = 1;
    }else if(center_x > 160 && center_x < 319 && center_y > 0 && center_y < 120){
      quad = 2;
    }else if(center_x > 0 && center_x < 160 && center_y > 120 && center_y < 239){
      quad = 3;
    }else if(center_x > 160 && center_x < 319 && center_y > 120 && center_y < 239){
      quad = 4;
    }
    
}

/*
//When new object is created
void Bounds::newObject()
{
}

void Bounds::detectCollision()
{

}


//Will Take in list of all objects
//void Bounds::check_Bounds(){
*/





