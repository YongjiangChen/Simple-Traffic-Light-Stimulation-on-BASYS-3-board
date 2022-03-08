/******************************************************************************
*

* File Name: gpio_init.h

* Project Name: TrafficLightWithExtraFestures
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7
* FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yongjiang Chen
* Company: University of Edinburgh
* Creation Date and Time: 28/11/2021; 12:00;
* Description: This header file contains definitions for the gpios used in this application
* including the VGA region Gpios and LED Gpios and 7-segment Gpios and button Gpios
*
******************************************************************************/

#ifndef __GPIO_INIT_H_
#define __GPIO_INIT_H_

#include "xgpio.h"		// Added for xgpio object definitions

XStatus initGpio(void);

// Display regions
XGpio  REGION_0_COLOUR;
XGpio  REGION_1_COLOUR;
XGpio  REGION_2_COLOUR;
XGpio  REGION_3_COLOUR;
XGpio  REGION_4_COLOUR;
XGpio  REGION_5_COLOUR;
XGpio  REGION_6_COLOUR;
XGpio  REGION_7_COLOUR;
XGpio  REGION_8_COLOUR;
XGpio  REGION_9_COLOUR;
XGpio  REGION_10_COLOUR;
XGpio  REGION_11_COLOUR;

// UP button for the pedestrian button
XGpio P_BTN_U;

// LEDs display
XGpio LEDs;

// 7-seg display
XGpio SEG7_HEX_OUT;
XGpio SEG7_SEL_OUT;

XGpio SWITCHES;

#endif
