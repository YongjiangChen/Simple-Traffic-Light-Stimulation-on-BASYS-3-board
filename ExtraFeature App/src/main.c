/******************************************************************************
*
*File Name: main.c
*Project Name: 7 Segment Application
*Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7
*FPGA)
*Tool Version: Xilinx SDK 2015.2
*Name: Yongjiang Chen
*Company: University of Edinburgh
*Creation Date and Time: 08/11/2021; 03:15
*Description: This source file contains functions used to drive the whole application.
* There are 5 functions in this file:
* checkSlideswitch() read input from the slide switchs and assign them to the corresponding variables
* checkButton() read input from the up button and assign 1 if the pedestrianButton is pressed
* writeDisplay() writes all variables to their corresponding gpios for correct output
* switchMode() helps to switch between the extra features.
* main() to sum up the initGpio() and setUpInterruptSystem() functions along with the switchMode() to start the application
******************************************************************************/

#include <stdio.h>
#include "platform.h"
#include "gpio_init.h"
#include "seg7_display.h"
#include "main.h"


// Number to be displayed on the screen
extern u16 disp_number;

// Boolean flag denoting whether an interrupt has been serviced
volatile int interruptServiced = FALSE;

// Methods declarations
XStatus initGpio();
XStatus setUpInterruptSystem();
void checkSlideswitch();
void checkButton();
void writeDisplay();
void switchMode();


void checkSlideswitch() {  // read input from the slide switchs and assign them to the corresponding variables
	slideSwitchIn = XGpio_DiscreteRead(&SWITCHES, 1);
	modeSwitch = slideSwitchIn & 0x001F;
	duration = slideSwitchIn>>4;
}

void checkButton(){ // read input from the up button
	pedestrianButton = XGpio_DiscreteRead(&P_BTN_U, 1);
}

void writeDisplay() {
	// Write colours to the first traffic light
	XGpio_DiscreteWrite(&REGION_0_COLOUR, 1, colour_0);
	XGpio_DiscreteWrite(&REGION_1_COLOUR, 1, colour_1);
	XGpio_DiscreteWrite(&REGION_2_COLOUR, 1, colour_2);

	// Write colours to the second traffic light
	XGpio_DiscreteWrite(&REGION_3_COLOUR, 1, colour_3);
	XGpio_DiscreteWrite(&REGION_4_COLOUR, 1, colour_4);
	XGpio_DiscreteWrite(&REGION_5_COLOUR, 1, colour_5);

	// Write colours to the sthird traffic light
	XGpio_DiscreteWrite(&REGION_6_COLOUR, 1, colour_6);
	XGpio_DiscreteWrite(&REGION_7_COLOUR, 1, colour_7);
	XGpio_DiscreteWrite(&REGION_8_COLOUR, 1, colour_8);

	// Write colour to the pedestrian light
	XGpio_DiscreteWrite(&REGION_10_COLOUR, 1, pd_colour);

	// Write value to LEDs
	XGpio_DiscreteWrite(&LEDs, 1, led_out);
}

// Method to switch between the extra features
void switchMode() {
	while (1)
	{
		writeDisplay();
		// Read the value from the pedestrian button
		checkButton();

		checkSlideswitch();

		switch(modeSwitch) {
		case 0:
			displayNumber(disp_number);
			duration = 0;
			break;
		case 1:  //quarantine mode
			displayDash();
			led_out = 0x9200;
			colour_0 = RED;
			colour_1 = WHITE;
			colour_2 = WHITE;
			colour_3 = RED;
			colour_4 = WHITE;
			colour_5 = WHITE;
			colour_6 = RED;
			colour_7 = WHITE;
			colour_8 = WHITE;
			pd_colour = RED;
			break;
		case 2: //Disable the pedestrian press button
			pedestrianButton = 0;
			displayNumber(disp_number);
			break;
		case 4:   //Colour blind mode
			displayNumber(disp_number);
			break;
		case 8:  // freeze the moment mode
			displayNumber(disp_number);
			break;
		default:
			displayNumber(disp_number);
			duration = 0;
		}

		// Wait for the interrupt to be serviced
		while (!interruptServiced);
	}
}

int main()
{
	init_platform();

	// Initialize all the Gpios and check if everything worked correctly
	XStatus status = initGpio();
	if (status != XST_SUCCESS)
	{
		print("GPIOs initialisation failed!!!\n\r");
		cleanup_platform();
		return 0;
	}

	print("GPIOs successfully initialised.\n\r");

	// Set up the interrupt system and perform a similar check as before
	status = setUpInterruptSystem();
	if (status != XST_SUCCESS)
	{
		print("Something wrong with interrupt!\n\r");
		cleanup_platform();
		return 0;
	}

	print("Interrupt successfully set.\n\r");

	// Call switch feature function and loop forever
	switchMode();

	cleanup_platform();
	return 0;
}


