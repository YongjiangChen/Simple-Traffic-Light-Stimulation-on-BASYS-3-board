/******************************************************************************
*

* File Name: interrupter.h



* Project Name: TrafficLightWithExtraFestures
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7
* FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yongjiang Chen
* Company: University of Edinburgh
* Creation Date and Time: 28/11/2021; 12:00;
* Description: This header file contains reference to the variables declared in the main.h and also definitions
* to the functions in the interrupter.c
*
******************************************************************************/



#ifndef INTERRUPT_H_
#define INTERRUPT_H_


// The variables are declared and commented in main.h
extern int state_1;
extern int state_2;
extern int state_3;

extern u16 colour_0;
extern u16 colour_1;
extern u16 colour_2;

extern u16 colour_3;
extern u16 colour_4;
extern u16 colour_5;

extern u16 colour_6;
extern u16 colour_7;
extern u16 colour_8;

extern u16 pd_colour;


extern u16 led_out;
extern u16 pedestrianButton;

extern int interruptServiced;

extern int modeSwitch;
extern u16 duration;

extern u64 RED;
extern u64 YELLOW;
extern u64 GREEN;
extern u64 WHITE;
extern u64 GREENBLUE;

void updateStates();


#endif
