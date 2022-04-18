#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <errno.h>
#include "DE1SoCfpga.h"

using namespace std;

DE1SoCfpga::DE1SoCfpga () {
        // Open /dev/mem to give access to physical addresses
      	fd = open( "/dev/mem", (O_RDWR | O_SYNC));
      	if (fd == -1)			//  check for errors in openning /dev/mem
      	{
              cout << "ERROR: could not open /dev/mem..." << endl;
              exit(1);
      	};
      	
         // Get a mapping from physical addresses to virtual addresses 1st one
         char *virtual_base = (char *)mmap (NULL, BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
         char *virtual_base2 = (char *)mmap (NULL, BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, ONCHIP_BASE);
         if (virtual_base == MAP_FAILED)		// check for errors
         {
            cout << "ERROR: mmap() failed..." << endl;
            close (fd);		// close memory before exiting
            exit(1);        // Returns 1 to the operating system;
         }
         pBase = virtual_base;
         pBase2 = virtual_base2;
        }
        
DE1SoCfpga::~DE1SoCfpga () {
        clearScreen(0, 0, 319, 239, 0);
        if (munmap (pBase, BRIDGE_SPAN) != 0)
      	{
            cout << "ERROR: munmap() failed..." << endl;
            exit(1);
      	}
        if (munmap (pBase2, BRIDGE_SPAN) != 0)
      	{
            cout << "ERROR: munmap() failed..." << endl;
            exit(1);
      	}
       
         close (fd); 	// close memory
        };

void DE1SoCfpga::Draw(unsigned int offset, int value)
        {
          * (volatile unsigned int *)(pBase2 + offset) = value; 
        }
void DE1SoCfpga::RegisterWrite(unsigned int offset, int value)
        {
          * (volatile unsigned int *)(pBase + offset) = value; 
        }
int DE1SoCfpga::RegisterRead(unsigned int offset)
        {
          return * (volatile unsigned int *)(pBase + offset); 
        }
void DE1SoCfpga::clearScreen(int x_1, int y_1, int x_2, int y_2, short pixel_color)
{
  int pixel_ptr, row, col;

	/* assume that the box coordinates are valid */
	for (row = y_1; row <= y_2; row++) {
		for (col = x_1; col <= x_2; ++col)  {
			pixel_ptr = 0 + (row << 10) + (col << 1);
			RegisterWrite(pixel_ptr, pixel_color);
		}
  }
}

int DE1SoCfpga::readKeypad()
{
  unsigned int input = (85 << 15);
  int mask;
  int N;
  int shift = 0;
  int key = 1;
  char button;
  //Set Columns to outputs and rows as inputs
  RegisterWrite(DIRECTION_REGISTER, input);
  
  //Need to scan columns in sequence
  for(int i=0; i<4; i++){
    RegisterWrite(DATA_REGISTER, input); //Sets columns as 1111
    if(i == 0){
      mask = ~(1 << 21);
      N = mask & input;
      RegisterWrite(DATA_REGISTER, N);
    }else if(i ==1){
      mask = ~(1 << 19);
      N = mask & input;
      RegisterWrite(DATA_REGISTER, N);
    }else if(i ==2){
      mask = ~(1 << 17);
      N = mask & input;
      RegisterWrite(DATA_REGISTER, N); 
    }else if(i ==3){
      mask = ~(1 << 15);
      N = mask & input;
      RegisterWrite(DATA_REGISTER, N); 
    }
    //Check each row for HIGH value
    unsigned int temp = RegisterRead(DATA_REGISTER);
    //cout << hex << temp << endl;
    int ROW0 = (~temp >> 9) & 1;
    int ROW1 = (~temp >> 11) & 1;
    int ROW2 = (~temp >> 13) & 1;
    int ROW3 = (~temp >> 14) & 1;
    //cout << ROW0;
    //cout << ROW1;
    //cout << ROW2;
    //cout << ROW3;
      
    if(i == 0){
      if(ROW0 == 1){
        key = key << shift;
      }else if(ROW1 == 1){
        key = key << (shift+1);
      }else if(ROW2 == 1){
        key = key << (shift+2); 
      }else if(ROW3 == 1){
        key = key << (shift+3); 
      }  
    }else if(i == 1){
      if(ROW0 == 1){
        key = key << (shift+4);
      }else if(ROW1 == 1){
        key = key << (shift+5);
      }else if(ROW2 == 1){
        key = key << (shift+6); 
      }else if(ROW3 == 1){
        key = key << (shift+7); 
      }  
    }else if(i == 2){
      if(ROW0 == 1){
        key = key << (shift + 8);
      }else if(ROW1 == 1){
        key = key << (shift+9);
      }else if(ROW2 == 1){
        key = key << (shift+10); 
      }else if(ROW3 == 1){
        key = key << (shift+11); 
      }  
    }else if(i == 3){
      if(ROW0 == 1){
        key = key << (shift+12);
      }else if(ROW1 == 1){
        key = key << (shift+13);
      }else if(ROW2 == 1){
        key = key << (shift+14); 
      }else if(ROW3 == 1){
        key = key << (shift+15); 
      }  
    }
    
    
  }

    /*
    if(key == 1){
      button = 49;
    }else if (key == 2){
      button = 52;
    }else if (key == 4){
      button = 55;
    */
    if (key == 8){ //D key --> we want this to be scale bigger
      return 6;
    //}else if (key == 16){ 
    }else if (key == 32){ //6key - we want this to be shiftRight
      return 2;
    }else if (key == 64){
      button = 56;
    }else if (key == 128){ //This is the # key --> scale smaller
      return 5;
    }else if (key == 256){ // Shift up
      return 1;
      cout << "OOGA" << endl;
    }else if (key == 512){
      button = 54;
    }else if (key == 1024){//8 key - want this to be shiftDown
      return 3;
    }else if (key == 2048){
      button = 35;
    }else if (key == 4096){
      button = 65;
    }else if (key == 8192){ //This is 4 key --> we want this to be shiftLeft
      return 4;
    }else if (key == 16384){
      button = 67;
    }else if (key == 32768){ //This is * key --> next object
      return 7;
    }else{
      return 0;
    }
    
    
    
  
}




