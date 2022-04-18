#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>

#include "DE1SoCfpga.h"
#include "Pixel.h"
#include "Box.h"
#include "Polygon.h"
#include "Bounds.h"


#define starting_x1 100
#define starting_y1 100
#define starting_x2 150
#define starting_y2 150

using namespace std;


//Global Variables
int number_objects = 10; //Number of created objects

int size = 3;
int *hitbox;



int triangle[6] = {110, 120, /* (x1,y1) */
                  120, 100,   /* (x2,y2) */
                  150, 100};  /* (x3,y3) */
int triangle2[6] = {160,10,
                  180,30,
                  150,30};
int star[20] = {20,118,
                    18,114,
                    14,114,
                    18,112,
                    16,108,
                    20,110,
                    24,108,
                    22,112,
                    26,114,
                    24,114};
int lshape[12] = {150,10,
                  160,10,
                  160,20,
                  180,20,
                  180,30,
                  150,30};
                  
int tshape[16] = {50,50,
                 50,60,
                 55,60,
                 55,70,
                 65,70,
                 65,60,
                 70,60,
                 70,50};
int vshape[12] = {40,50,
                  45,50,
                  50,60,
                  55,50,
                  60,50,
                  50,70};

int box[8] = {50,50,60,50,60,60,50,60};
int xshape[24] = {40,60,45,60,45,65,50,65,50,70,45,70,45,75,40,75,40,70,35,70,35,65,40,65};
int pentagon[10] = {50,50,
                    60,60,
                    60,65,
                    40,65,
                    40,60};
int hexagon[12] = {50,50,
                    60,60,
                    60,65,
                    50,60,
                    40,65,
                    40,60};
int para[8] = {50,50,
                60,50,
                65,60,
                55,60};
int octagon[16] = {40,50,
                  50,50,
                  60,60,
                  60,70,
                  50,80,
                  40,80,
                  30,70,
                  30,60};
 

int main() { 
  DE1SoCfpga *client = new DE1SoCfpga();
  double elapsedtime;
  
  Polygon *shapes[10]; //Holds Polygon of objects
  shapes[0]=new Polygon(3, triangle, 1, 1);
  shapes[1]=new Polygon(6, lshape, 1, 1);
  shapes[2]=new Polygon(8, tshape, 1, 1);
  shapes[3]=new Polygon(4, box, 1,1);
  shapes[4]=new Polygon(6, vshape,1,1);
  shapes[5]=new Polygon(12, xshape, 1,1);
  shapes[6]=new Polygon(5, pentagon, 1,1);
  shapes[7]=new Polygon(6, hexagon, 1,1);
  shapes[8]=new Polygon(4, para, 1,1);
  shapes[9]=new Polygon(8, octagon, 1,1);
  
  //While loop to initialize objects at empty space
  for(int i = 0; i<4; i++){
    int check = 0;
    shapes[i]->drawPolygon();
    while(check == 0){
      int keypad = client->readKeypad();
      if(keypad == 1){
        shapes[i]->shiftUp();  
      }else if(keypad == 2){
        shapes[i]->shiftRight();
      }else if(keypad == 3){
        shapes[i]->shiftDown();
      }else if(keypad == 4){
        shapes[i]->shiftLeft();
      }else if(keypad == 5){
        shapes[i]->Scaling(.5);
      }else if(keypad == 6){
        shapes[i]->Scaling(1.5);
      }else if(keypad == 7){
        check = 1;
        //Go to next object so END loop
      }
      unsigned int microsecond = 500000;
      usleep(1 * microsecond);//sleeps for debugging
    }
    cout << "Object ";
    cout << i;
    cout << " Initalized" << endl;
  }
  
 
  
  
  int end = 1;
  int play = 0;
  int rotation = 0;
  
  int counter= 10000000;
  client->RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET, counter);
  client->RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET, 3);
  
  
  while (client->RegisterRead(SW_OFFSET) == 0) {
    if (client->RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET) != 0) {
      client->RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET, 1); // reset timer flag bit
      if (rotation == 10){
        rotation = 0;
        shapes[0]->Rotate();
        shapes[1]->Rotate();
        shapes[2]->Rotate();
        shapes[3]->Rotate();
        /*
        shapes[4]->Rotate();
        shapes[5]->Rotate();
        shapes[6]->Rotate();
        shapes[7]->Rotate();
        shapes[8]->Rotate();
        shapes[9]->Rotate();
        */
        
      }
      shapes[0]->Move();
      shapes[1]->Move();
      shapes[2]->Move();
      shapes[3]->Move();
      /*
      shapes[4]->Move();
      shapes[5]->Move();
      shapes[6]->Move();
      shapes[7]->Move();
      shapes[8]->Move();
      shapes[9]->Move();
      */
      
      //Start clock
      clock_t start = clock();
      
      
      shapes[0]->checkCollision(shapes[1]);
      shapes[0]->checkCollision(shapes[2]);
      shapes[0]->checkCollision(shapes[3]);
      /*
      shapes[0]->checkCollision(shapes[4]);
      shapes[0]->checkCollision(shapes[5]);
      shapes[0]->checkCollision(shapes[6]);
      shapes[0]->checkCollision(shapes[7]);
      shapes[0]->checkCollision(shapes[8]);
      shapes[0]->checkCollision(shapes[9]);
      */
      
      shapes[1]->checkCollision(shapes[2]);
      shapes[1]->checkCollision(shapes[3]);
      /*
      shapes[1]->checkCollision(shapes[4]);
      shapes[1]->checkCollision(shapes[5]);
      shapes[1]->checkCollision(shapes[6]);
      shapes[1]->checkCollision(shapes[7]);
      shapes[1]->checkCollision(shapes[8]);
      shapes[1]->checkCollision(shapes[9]);
      */
      
      shapes[2]->checkCollision(shapes[3]);
      /*
      shapes[2]->checkCollision(shapes[4]);
      shapes[2]->checkCollision(shapes[5]);
      shapes[2]->checkCollision(shapes[6]);
      shapes[2]->checkCollision(shapes[7]);
      shapes[2]->checkCollision(shapes[8]);
      shapes[2]->checkCollision(shapes[9]);
      
      shapes[3]->checkCollision(shapes[4]);
      shapes[3]->checkCollision(shapes[5]);
      shapes[3]->checkCollision(shapes[6]);
      shapes[3]->checkCollision(shapes[7]);
      shapes[3]->checkCollision(shapes[8]);
      shapes[3]->checkCollision(shapes[9]);
      
      shapes[4]->checkCollision(shapes[5]);
      shapes[4]->checkCollision(shapes[6]);
      shapes[4]->checkCollision(shapes[7]);
      shapes[4]->checkCollision(shapes[8]);
      shapes[4]->checkCollision(shapes[9]);
      
      shapes[5]->checkCollision(shapes[6]);
      shapes[5]->checkCollision(shapes[7]);
      shapes[5]->checkCollision(shapes[8]);
      shapes[5]->checkCollision(shapes[9]);
      
      shapes[6]->checkCollision(shapes[7]);
      shapes[6]->checkCollision(shapes[8]);
      shapes[6]->checkCollision(shapes[9]);
      
      shapes[7]->checkCollision(shapes[8]);
      shapes[7]->checkCollision(shapes[9]);
      
      shapes[8]->checkCollision(shapes[9]);
      */
      
      //Stop clock
      clock_t end = clock();
      elapsedtime = double(end - start)/CLOCKS_PER_SEC;
       
      cout << "TOTAL TIME MEASURED: " << elapsedtime << " seconds" << endl;
      
      
      
      
      cout<< "collisions" << endl;

      
      shapes[0]->checkMonitor();
      shapes[1]->checkMonitor();
      shapes[2]->checkMonitor();
      shapes[3]->checkMonitor();
      /*
      shapes[4]->checkMonitor();
      shapes[5]->checkMonitor();
      shapes[6]->checkMonitor();
      shapes[7]->checkMonitor();
      shapes[8]->checkMonitor();
      shapes[9]->checkMonitor();
      */
      
      rotation++;
    }
    
    
  }
  
  cout << "Enter 0 if you would like the program to end" << endl;
  cin >> end;
  if(end == 0){
    for(int j = 0; j < 3; j++){
      delete shapes[j];
    }
    delete client;
  }

  
  
  return 0;
  

}