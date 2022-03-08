/******************************************************************************
*

* File Name: main.h


* Project Name: TrafficLightWithExtraFestures
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7
* FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yongjiang Chen
* Company: University of Edinburgh
* Creation Date and Time: 28/11/2021; 12:00;
* Description: This header file contains declarations of variables to be assigned as  Colours for the three
*  traffic lights and The binary code for the LED display to indicate the traffic light/pedestrian light/ waiting light
*  Value of pedestrian button, 1 if pressed, 0 if not, variables to be used to changing the traffic light cycle
*  variable to hold the slide switch input, variable to select between different extra features and
*  variable to write the duration for traffic light cycles
*
*
******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#include "colours.h"

// Colours for the first traffic light
volatile u16 colour_0 = RED;
volatile u16 colour_1 = WHITE;
volatile u16 colour_2 = WHITE;

// Colours for the second traffic light
volatile u16 colour_3 = RED;
volatile u16 colour_4 = WHITE;
volatile u16 colour_5 = WHITE;

// Colours for the third traffic light
volatile u16 colour_6 = RED;
volatile u16 colour_7 = WHITE;
volatile u16 colour_8 = WHITE;

// Colour for the pedestrian light
volatile u16 pd_colour = RED;

// The binary code for the LED display to indicate the traffic light/pedestrian light/ waiting light
volatile u16 led_out = 0;

// Value of pedestrian button, 1 if pressed, 0 if not
volatile u16 pedestrianButton;

// variables to be used to change the traffic light cycle
volatile int state_1 = 0;
volatile int state_2 = 0;
volatile int state_3 = 0;

//variable to hold the slide switch input
volatile u16 slideSwitchIn;

//variable to select between different extra features
volatile int modeSwitch;

//variable to write the duration for traffic light cycles
volatile u16 duration = 0;

#endif
