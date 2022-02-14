// example to test the TFT Display
// Thanks to the GraphicsDisplay and TextDisplay classes
// test2.bmp has to be on the mbed file system
//Lib for 320*240 Pixel Color LCD with ILI9341 controller. Based on MI0283QT-9 datasheet

/* LED */
#include "lpc17xx.h"
#include <stdio.h>

/* LCD */
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include <string>
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"
#include "font_big.h"

#include "ultrasonic.h"


//LCD Pin
DigitalOut LCD_LED(P0_2); // the Watterott display has a backlight switch

SPI_TFT_ILI9341 TFT(P0_9, P0_8, P0_7, P0_6, P0_0, P0_1,"TFT"); // mosi, miso, sclk, cs, reset, dc


/* LED pin with 0.xx */

#define RED_PIN		15		//Red pin = 0.15
#define YELLOW_PIN	16		//Yellow pin = 0.16
#define GREEN_PIN	23		//Green pin = 0.23
#define WALK_PIN	4		//Walk pin = 0.4

/* LED waiting time */

#define RED_SEC		20
#define YELLOW_SEC	3
#define GREEN_SEC	15

/* 7-Segment pin with 2.xx */

#define A_SEGMENT_PIN	7		//A pin = 2.7
#define B_SEGMENT_PIN	6		//B pin = 2.6
#define C_SEGMENT_PIN	5		//C pin = 2.5
#define D_SEGMENT_PIN	4		//D pin = 2.4
#define E_SEGMENT_PIN	3		//E pin = 2.3
#define	F_SEGMENT_PIN	2		//F pin = 2.2
#define G_SEGMENT_PIN	1		//G pin = 2.1

/* Switch Pin with 2.xx */

#define BUTTON_A_PIN	11		//Button A = 2.11
#define BUTTON_B_PIN	10		//Button B = 2.10

// Locate LCD

#define NUM_POS_X	30
#define NUM_POS_Y	100

// Distance

int traffic_distance = 0;

void delay() {
	static int j;
	int count = 0;

	//make a delay with 1 sec
	for(j = 12000000; j > 0; j--)
		count++;
}

void countdown_segment(int num) {

	switch (num){
	case 0:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << E_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << F_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << G_SEGMENT_PIN;
		break;
	case 1:
		LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << G_SEGMENT_PIN;
		break;
	case 2:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << E_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	case 3:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	case 4:
		LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	case 5:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	case 6:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = false << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << E_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	case 7:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << G_SEGMENT_PIN;
		break;
	case 8:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << E_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	case 9:
		LPC_GPIO2->FIOCLR = 1 << A_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << B_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << C_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << D_SEGMENT_PIN;
		LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << F_SEGMENT_PIN;
		LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;
		break;
	}
}

void dist(int distance)
{
	TFT.set_font((unsigned char*) Arial12x12);

	//print out the distance
	//put code here to execute when the distance has changed
	TFT.locate(0, 225);
	TFT.printf("Distance %d mm\r   \n", distance);

	//Save the traffic distance
	traffic_distance = distance;
}

//Set the trigger pin to p6 and the echo pin to p7
//have updates every .1 seconds and a timeout after 1
//second, and call dist when the distance changes
ultrasonic mu(P0_10, P0_11, .1, 1, &dist);

int main() {

	//SystemInit();

	// P0.15 & P0.16 & P0.23 = Outputs (GPIO 0, with switch pin 15&16&23 --> set to output)
	LPC_GPIO0->FIODIR |= (1 << GREEN_PIN) | (1 << YELLOW_PIN) | (1 << RED_PIN) |
						(1 << WALK_PIN);

	// Turn-OFF LED
	LPC_GPIO0->FIOCLR |= 1 << GREEN_PIN;
	LPC_GPIO0->FIOCLR |= 1 << YELLOW_PIN;
	LPC_GPIO0->FIOCLR |= 1 << RED_PIN;
	LPC_GPIO0->FIOCLR |= 1 << WALK_PIN;

	// 7-Segment --> set to be output
	// Push Button --> set to be input
	LPC_GPIO2->FIODIR |= (1 << A_SEGMENT_PIN) | (1 << B_SEGMENT_PIN) | (1 << C_SEGMENT_PIN) |
						(1 << D_SEGMENT_PIN) | (1 << E_SEGMENT_PIN) | (1 << F_SEGMENT_PIN) |
						(1 << G_SEGMENT_PIN) | ~(1 << BUTTON_A_PIN) | ~(1 << BUTTON_B_PIN);

	// Turn-OFF 7-Segment
	LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
	LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
	LPC_GPIO2->FIOSET = true << C_SEGMENT_PIN;
	LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
	LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
	LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
	LPC_GPIO2->FIOSET = true << G_SEGMENT_PIN;


	/* --------------------------------------------------------------- */

	// Setup LCD
	LCD_LED = 1;  // backlight on

	TFT.claim(stdout);      // send stdout to the TFT display
	TFT.set_orientation(1);
	TFT.background(Black);    // set background to black
	TFT.foreground(White);    // set chars to white
	TFT.cls();                // clear the screen

	TFT.set_font((unsigned char*) Arial28x28);
	TFT.locate(NUM_POS_X, NUM_POS_Y);

	/* --------------------------------------------------------------- */

	//start measuring the distance
    mu.startUpdates();

	//declare counting number
	int green_count = 0;
	int yellow_count = 0;
	int red_count = 0;

	//status of the counting led
	//0 --> first started counting
	//1 --> counting green
	//2 --> counting yellow
	//3 --> counting red
	int status = 0;

	//button state
	bool a_state = false, b_state = false;
	bool button_enable = false;

	int heavy_traffic_count = 0;

	//looping every 1 sec until get interrupted
	while(1) {

		mu.checkDistance();     //call checkDistance() as much as possible, as this is where
								//the class checks if dist needs to be called.

		//check if the car is near
		if (traffic_distance < 100) {
			heavy_traffic_count++;
		} else {
			heavy_traffic_count = 0;
		}

		//get button state and print out (only when it enabled)
		if (button_enable == true) {
			a_state = (LPC_GPIO2->FIOPIN >> BUTTON_A_PIN) & 1;
			b_state = (LPC_GPIO2->FIOPIN >> BUTTON_B_PIN) & 1;

			TFT.set_font((unsigned char*) Arial12x12);

			//clear the button state
			TFT.locate(0,0);
			printf("a_state = 0   b_state = 0          ");

			//print out button state
			TFT.locate(0,0);
			printf("a_state = %d   b_state = %d", a_state, b_state);
		}
		else {
			TFT.set_font((unsigned char*) Arial12x12);
			TFT.locate(0,0);
			printf("a_state = false   b_state = false");
		}


		//press a button
		if (a_state == true || b_state == true) {
			//change to red light when green shows up
			if (green_count > 9) {
				green_count = 9;
			}

			//update button state to false
			a_state = false;
			b_state = false;
			button_enable = false;

			continue;
		}

		//first time count --> assign red to the counter
		else if (status == 0) {
			red_count = RED_SEC;					// set the time to be countdown
			status = 3;

			LPC_GPIO0->FIOSET = 1 << RED_PIN;		// Turn-On Red

			//turn off 7-segment
			LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
			LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
			LPC_GPIO2->FIOSET = true << C_SEGMENT_PIN;
			LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
			LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
			LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
			LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;

			LPC_GPIO0->FIOSET = 1 << WALK_PIN;		// Turn-On Walk Way LED
		}

		else {
			//countdown the green and assign yellow when it reaches 0
			if (status == 1) {
				if (green_count == 0){
					yellow_count = YELLOW_SEC;
					status = 2;

					LPC_GPIO0->FIOCLR = 1 << GREEN_PIN;		// Clear Green
					LPC_GPIO0->FIOSET = 1 << YELLOW_PIN;	// Turn-ON Yellow

					//turn off 7-segment
					LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << C_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
					LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;

					//clear the number
					TFT.set_font((unsigned char*) Arial28x28);
					TFT.locate(NUM_POS_X, NUM_POS_Y);
					TFT.printf("Yellow Light:     ");

					button_enable = false;
					continue;
				}

				countdown_segment(green_count);				// show the number on 7-Segment

				//print out green light count
				TFT.set_font((unsigned char*) Arial28x28);
				TFT.locate(NUM_POS_X, NUM_POS_Y);
				TFT.printf("Green Light: %d  ", green_count);

				delay();

				green_count--;
			}

			// countdown the yellow and assign red when it reaches 0
			if (status == 2) {
				if (yellow_count == 0) {
					red_count = RED_SEC;
					status = 3;

					LPC_GPIO0->FIOCLR = 1 << YELLOW_PIN;	// Clear Yellow
					LPC_GPIO0->FIOSET = 1 << RED_PIN;		// Turn-On Red

					//turn off 7-segment
					LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << C_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
					LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;

					//clear the number
					TFT.set_font((unsigned char*) Arial28x28);
					TFT.locate(NUM_POS_X, NUM_POS_Y);
					TFT.printf("Red Light:     ");

					LPC_GPIO0->FIOSET = 1 << WALK_PIN;		// Turn-ON Cross Way LED
					continue;
				}

				countdown_segment(yellow_count);			// show the number on 7-Segment

				//print out yellow light count
				TFT.set_font((unsigned char*) Arial28x28);
				TFT.locate(NUM_POS_X, NUM_POS_Y);
				TFT.printf("Yellow Light: %d  ", yellow_count);

				delay();

				yellow_count--;
			}

			//countdown the red and assign green when it reaches 0
			if (status == 3) {
				if (red_count == 0) {
					green_count = GREEN_SEC;
					status = 1;

					LPC_GPIO0->FIOCLR = 1 << RED_PIN;		// Clear Red
					LPC_GPIO0->FIOSET = 1 << GREEN_PIN;		// Turn-ON Green

					//turn off 7-segment
					LPC_GPIO2->FIOSET = true << A_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << B_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << C_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << D_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << E_SEGMENT_PIN;
					LPC_GPIO2->FIOSET = true << F_SEGMENT_PIN;
					LPC_GPIO2->FIOCLR = 1 << G_SEGMENT_PIN;

					//Clear the number
					TFT.set_font((unsigned char*) Arial28x28);
					TFT.locate(NUM_POS_X, NUM_POS_Y);
					TFT.printf("Green Light:     ");

					button_enable = true;
					LPC_GPIO0->FIOCLR = 1 << WALK_PIN;		// Clear Walk Way LED
					continue;
				}

				//reduce red light time if >= 9
				if (heavy_traffic_count >= 5) {
					if (red_count > 9) {
						red_count = 9;
					}
				}

				countdown_segment(red_count);				// show the number on 7-Segment

				//print out red light count
				TFT.set_font((unsigned char*) Arial28x28);
				TFT.locate(NUM_POS_X, NUM_POS_Y);
				TFT.printf("Red Light: %d  ", red_count);

				delay();

				red_count--;
			}
		}
	}

	return 0;
}

