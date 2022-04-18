#ifndef Box_H
#define Box_H
#include <iostream>
#include "DE1SoCfpga.h"
using namespace std;

class Box: public DE1SoCfpga {
    private:
      int x1;
      int y1;
      int x2;
      int y2;
      int length;
      int height;
      int flow_control;
      int current_orientation; 
    public:
        Box(int input_x1, int input_y1, int input_x2, int input_y2);
        ~Box();
        void Set_Length();
        void Set_Height();
        void Set_Orientation();
        int Check_Orientation();
        void Swap_Coordinates();
        void Box_Create(int x_1, int y_1, int x_2, int y_2, short pixel_color);
        void Screen_Clear();
        void Box_Clear();
        void Box_Rotate();
        void Box_Flow_right();
        void Box_Flow_left();
        void Box_Flow_down();
        void Box_Flow_up();
        void Box_Collision();
        
};

#endif