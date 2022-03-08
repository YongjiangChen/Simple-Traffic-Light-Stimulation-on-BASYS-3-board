/******************************************************************************
*
* File Name: gpio.c
* Project Name: TrafficLightWithExtraFestures
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7
* FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yongjiang Chen
* Company: University of Edinburgh
* Creation Date and Time: 28/11/2021; 12:00;
* Description: This source file contains function initGpio used to initialise gpios used in the application
* including Initalise the 12 VGA Display regions, initialise the LEDs, initialise the 7-seg display
* initialise the pedestrian button, which is the up button and initialise the slideswitchs

*
******************************************************************************/

#include "gpio_init.h" // Add the gpio definitions

XStatus initGpio()
{
	XStatus status;


	// Initalising the 12 VGA Display regions
	status = XGpio_Initialize(&REGION_0_COLOUR, 7);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_1_COLOUR, 10);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_2_COLOUR, 11);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_3_COLOUR, 12);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_4_COLOUR, 13);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_5_COLOUR, 14);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_6_COLOUR, 15);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_7_COLOUR, 16);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_8_COLOUR, 17);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_9_COLOUR, 18);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_10_COLOUR, 8);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&REGION_11_COLOUR, 9);

	if (status != XST_SUCCESS)
		return XST_FAILURE;


	// initialise the LEDs
	status = XGpio_Initialize(&LEDs, 2);

	if (status != XST_SUCCESS)
		return XST_FAILURE;


	// initialise the 7-seg display
	status = XGpio_Initialize(&SEG7_HEX_OUT, 0);

	if (status != XST_SUCCESS)
		return XST_FAILURE;

	status = XGpio_Initialize(&SEG7_SEL_OUT, 1);

	if (status != XST_SUCCESS)
		return XST_FAILURE;


	// initialise the pedestrian button, which is the up button
	status = XGpio_Initialize(&P_BTN_U, 6);

	if (status != XST_SUCCESS)
		return XST_FAILURE;


	// initialise the slideswitchs
	status = XGpio_Initialize(&SWITCHES, 19);

	if (status != XST_SUCCESS)
		return XST_FAILURE;


	return XST_SUCCESS;
}

