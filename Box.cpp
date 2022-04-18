#include "Box.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

#define BLUE 0x187F



Box::Box(int input_x1, int input_y1, int input_x2, int input_y2) {
  flow_control = 0;
  x1 = input_x1;
  y1 = input_y1;
  x2 = input_x2;
  y2 = input_y2;
  Box_Create(x1, y1, x2, y2, BLUE);
}

Box::~Box() {
  Screen_Clear();
}

void Box::Set_Length()
{
  length = x2 - x1;
}

void Box::Set_Height()
{
  height = y2 - y1;
}
void Box::Set_Orientation()
{
  cout << ("Yo") << endl;
}

int Box::Check_Orientation()
{
  return current_orientation;
}
void Box::Swap_Coordinates()
{
  int temp_1 = x1;
  int temp_2 = x2;
  x1 = y1;
  x2 = y2;
  y1 = temp_1;
  y2 = temp_2;
  
}
          
//Creates Box
void Box::Box_Create(int x_1, int y_1, int x_2, int y_2, short pixel_color)
{
  int pixel_ptr, row, col;

	/* assume that the box coordinates are valid */
	for (row = y_1; row <= y_2; row++) {
		for (col = x_1; col <= x_2; ++col)  {
			pixel_ptr = 0 + (row << 10) + (col << 1);
			RegisterWrite(pixel_ptr, pixel_color);
		}
  }
  Set_Length();
  Set_Height();
}

void Box::Screen_Clear() 
{
  Box_Create(0, 0, 319, 239, 0);
}

void Box::Box_Clear()
{
  Box_Create(x1,y1,x2,y2, 0);
}

//Box_Flow_x Corresponds to When Starting Orientation is 1
//Box_Flow_y Corresponds to When Starting Orientation is 0

void Box::Box_Rotate()
{
  
}
void Box::Box_Flow_right()
{
  x1 = x2;
  x2 = x2 + length;
  Box_Create(x1,y1,x2,y2, BLUE);
  
}

void Box::Box_Flow_left()
{
  x2 = x1;
  x1 = x1 - length;
  Box_Create(x1,y1,x2,y2, BLUE);
  
}


void Box::Box_Flow_down()
{
  y1 = y2;
  y2 = y2 + height;
  Box_Create(x1,y1,x2,y2, BLUE);
  
}

void Box::Box_Flow_up()
{
  y2 = y1;
  y1 = y1 - height;
  Box_Create(x1,y1,x2,y2, BLUE);
  
}

void Box::Box_Collision()
{
  //Check Edges if they touch any parts of monitor
  if(flow_control == 0){
    Box_Flow_right();
  }else if (flow_control == 1){
    Box_Flow_left();
  }else if (flow_control == 2){
    Box_Flow_down();
  }else if (flow_control == 3){
    Box_Flow_up();
  }
  //Check any interactions with other objects
  //Check right edge
  if(x2 >= 319){
    flow_control = 1;
  }else if(x1 <=0){ //left edge
    flow_control = 0;
  }else if(y1 <=0){ //top edge
    flow_control = 2;
  }else if(y2 >= 239){ //bottom edge
    flow_control = 3;
  }

  
  
}


