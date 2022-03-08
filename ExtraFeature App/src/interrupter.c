/******************************************************************************
*
* File Name: seg7_display.c
* Project Name: TrafficLightWithExtraFestures
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7
* FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yongjiang Chen
* Company: University of Edinburgh
* Creation Date and Time: 28/11/2021; 12:00;
* Description: This source file contains functions used to control the traffic light cycles with an interrupter
* It has 6 functions: setColours() sets the VGA colour for each of the traffic light,
* setLED() sets the corresponding LED for each traffic light display and the pedestrian light and the waiting light
* blink() makes the pedestrian light to blink in the last two seconds of its display
* enablePedestrian() controls the pedestrian light display and display duration
* updateStates() controls the traffic lights display cycle
*  hwTimerISR(void *CallbackRef) (which is defined in the xinterruptES3.c file) method is used to call updateStates()
*  and enablePedestrian() whenever appropriate to control this traffic light system
*
******************************************************************************/
#include "xil_types.h"
#include "seg7_display.h"
#include "gpio_init.h"
#include "interrupter.h"
#include "colours.h"

// Variable that will hold the number of interrupts, in order to determine when a second has passed etc.
u16 interruptCounter = 0;

// Initial value of the number to be displayed on the 7-segment
volatile u16 disp_number;

// Boolean checkers
int waiting = 0; // Is pedestrian waiting?
int crossing = 0; // Is pedestrian crossing?
int traffic1_ok = 0; // Has TR1 finished its cycle?
int traffic2_ok = 0; // Has TR2 finished its cycle?
int traffic3_ok = 1; // Has TR3 finished its scycle?
int just_crossed = 0; // Was a pedestrian just allowed to cross?

// Time counter for when a pedestrian is going to cross
u16 count = 0;

void setColours()
{
	// Based on state of Traffic light 1, set the values of colour regions 0 to 2
	switch (state_1)
	{
		// RED
		case 0:
			colour_0 = RED;
			colour_1 = WHITE;
			colour_2 = WHITE;
			break;
		// RED + YELLOW
		case 1:
			colour_0 = RED;
			colour_1 = YELLOW;
			colour_2 = WHITE;
			break;
		// GREEN
		case 2:
			colour_0 = WHITE;
			colour_1 = WHITE;
			colour_2 = GREEN;
			if(modeSwitch == 4) {   //Colour blind GREEN display
				colour_2 = GREENBLUE;
			}
			break;
		// YELLOW
		case 3:
			colour_0 = WHITE;
			colour_1 = YELLOW;
			colour_2 = WHITE;
	}

	// Based on state of Traffic light 2, set the values of colour regions 3 to 5
	switch (state_2)
	{
		case 0:
			colour_3 = RED;
			colour_4 = WHITE;
			colour_5 = WHITE;
			break;
		case 1:
			colour_3 = RED;
			colour_4 = YELLOW;
			colour_5 = WHITE;
			break;
		case 2:
			colour_3 = WHITE;
			colour_4 = WHITE;
			colour_5 = GREEN;
			if(modeSwitch == 4) {
				colour_5 = GREENBLUE;
			}
			break;
		case 3:
			colour_3 = WHITE;
			colour_4 = YELLOW;
			colour_5 = WHITE;
	}
	// Based on state of Traffic light 3, set the values of colour regions 6 to 8
	switch (state_3)
	{
		case 0:
			colour_6 = RED;
			colour_7 = WHITE;
			colour_8 = WHITE;
			break;
		case 1:
			colour_6 = RED;
			colour_7 = YELLOW;
			colour_8 = WHITE;
			break;
		case 2:
			colour_6 = WHITE;
			colour_7 = WHITE;
			colour_8 = GREEN;
			if(modeSwitch == 4) {
				colour_8 = GREENBLUE;
			}
			break;
		case 3:
			colour_6 = WHITE;
			colour_7 = YELLOW;
			colour_8 = WHITE;
	}
}

void setLED()
{
	// Produce the LED value by checking the states of the three traffic lights
	if (state_1 == 0 && state_2 == 0 && state_3 == 0) {
		led_out = 0x9200;
	}else if (state_1 == 1) {
		led_out = 0xD200;
	}else if (state_1 == 2) {
		led_out = 0x3200;
	}else if (state_1 == 3) {
		led_out = 0x5200;
	}else if (state_2 == 1) {
		led_out = 0x9A00;
	}else if (state_2 == 2) {
		led_out = 0x8600;
	}else if (state_2 == 3) {
		led_out = 0x8A00;
	}else if (state_3 == 1) {
		led_out = 0x9300;
	}else if (state_3 == 2) {
		led_out = 0x9080;
	}else if (state_3 == 3) {
		led_out = 0x9100;
	}

}

void blink()
{
	// If the counter is within one of the five ranges, change the pedestrian light colour to white
	// This will give a blinking effect
	if ((count >= (750 + 250*duration) && count < (800 + 250*duration)) ||
		(count >= (850 + 250*duration) && count < (900 + 250*duration)) ||
		(count >= (950 + 250*duration) && count < (1000 + 250*duration)) ||
		(count >= (1050 + 250*duration) && count < (1100 + 250*duration)) ||
		(count >= (1150 + 250*duration) && count < (1200 + 250*duration))
	) {
		pd_colour = WHITE;
	}
}

int enablePedestrian()
{
	// the pedestrian can either waiting or crossing the road
	waiting = !crossing;

	// The third led on the right is the pedestrian led
	led_out = led_out ^ waiting << 3;

	// If all three lights are red, allow him to cross (after 1 seconds)
	if (state_1 == 0 && state_2 == 0 && state_3 == 0 && just_crossed != 1)
	{
		// Increment the crossing time counter
		count++;

		// Turn Pedestrian light green
		if (count <= (1250 + 250*duration))
		{
			// Indicate that the PD is not waiting anymore
			waiting = 0;
			crossing = 1; // He is crossing when crossing =1 and waiting = 0
			pd_colour = GREEN; // pedestrian light is green
			led_out = 0x9201;
			blink(); // Blink (if 2 seconds are left)
			disp_number = (5 + duration) - (count) / 251; // Decrement the time left for crossing
		}

		// If the pedestrian crossing time is over
		else if (count > (1250 + 250*duration))
		{
			crossing = 0; // Not crossing anymore
			pd_colour = RED;
			updateStates();
			count = 0;
			just_crossed = 1; // Just crossed, so the next pedestrian will only be allowed after next cycle
			interruptCounter = 0;
		}

		// Return 1 if pedestrian is allowed to cross now
		return 1;
	}

	return 0;
}

void updateStates()
{
	// It is true by default to start the cycle
	if (traffic3_ok)
	{
		state_1 = (state_1 + 1) % 4; // Go to next state
		traffic3_ok = state_1 == 0 ? 0 : 1; // Check if sequence is finished
		traffic2_ok = !traffic3_ok; // If first light is finished, make light 2 start
	}

	else if (traffic2_ok)
	{
		state_2 = (state_2 + 1) % 4;
		traffic2_ok = state_2 == 0 ? 0 : 1;
		traffic1_ok = !traffic2_ok; // If second light is finished, make light 3 start
	}

	else if (traffic1_ok)
	{
		state_3 = (state_3 + 1) % 4;
		traffic1_ok = state_3 == 0 ? 0 : 1;
		traffic3_ok = !traffic1_ok; // If third light is finished, make light 1 start again
	}

	// reset just_crossed so the pedestrian button is available again
	just_crossed = 0;

	// Set region colours and LED values appropriately for the current state
	setColours();
	setLED();
}

void hwTimerISR(void *CallbackRef)
{
	interruptServiced = FALSE;

	// Display the current value of disp_number
	displayDigit();

	// Check if the pedestrian button has been pressed or the pedestrian is waiting or crossing
	if(pedestrianButton || waiting || crossing) {
		if(enablePedestrian()) {
			interruptServiced = TRUE;
			return;
		}
	}

	if(modeSwitch == 1 || modeSwitch == 8) {  //pause the interrupter if the quarantine mode or the freeze mode is on
		interruptServiced = TRUE;
		return;
	}

	interruptCounter++;

	// 7-seg display countdown
	disp_number = (1+duration) - (interruptCounter) / 251;

	// Update state of the lights after 1 seconds
	if (interruptCounter == (250*(1+duration))){
		updateStates();
		interruptCounter = 0;
	}

	interruptServiced = TRUE;
}
