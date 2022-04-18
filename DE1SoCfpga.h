#ifndef DE1SoCfpga_H
#define DE1SoCfpga_H
#include <iostream>
using namespace std;



// 1st base address of FPGA Device FOR PIXEL BUFFER
const unsigned int ONCHIP_BASE 	= 0xC8000000;  // Base offset for FPGA on-chip memory

//2nd Base address for everything else
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;  // Base offset


// Length of memory-mapped IO window 
const unsigned int BRIDGE_SPAN 	= 0x00DEC700;  // Address map size

//Switch to turn off program
const unsigned int SW_OFFSET 		= 64;

//MPCORE Timer
const  unsigned  int  MPCORE_PRIV_TIMER_LOAD_OFFSET  =  0xDEC600;            //  Points  to LOAD Register
const  unsigned  int MPCORE_PRIV_TIMER_COUNTER_OFFSET  =  0xDEC604;        //  Points  to  COUNTER Register
const  unsigned  int  MPCORE_PRIV_TIMER_CONTROL_OFFSET  = 0xDEC608;        //  Points  to  CONTROL Register
const  unsigned  int  MPCORE_PRIV_TIMER_INTERRUPT_OFFSET  = 0xDEC60C;    //  Points  to  INTERRUPT Register


//For speakers
const unsigned int DATA_REGISTER = 96;
const unsigned int DIRECTION_REGISTER = 100;



class DE1SoCfpga
{
public:
        char *pBase;
        char *pBase2;
        int fd;
        
        DE1SoCfpga();
        ~DE1SoCfpga();
        void Draw(unsigned int offset, int value);
        void RegisterWrite(unsigned int offset, int value);
        int RegisterRead(unsigned int offset);
        void clearScreen(int x_1, int y_1, int x_2, int y_2, short pixel_color);
        int readKeypad();
};


#endif