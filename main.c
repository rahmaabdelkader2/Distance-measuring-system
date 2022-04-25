/*
 * main.c
 *
 *  Created on: Oct 20, 2021
 *      Author: Rahma abdelkader
 */

#include "LCD.h"
#include "avr/io.h"
#include "ICU.h"
#include "ULTRASONIC.h"



int main(void){

	uint16 Total_distance =0;

	   SREG |= (1<<7); //enable I bit

	   Ultrasonic_init();

	  /* intialize LCD */

	   LCD_init();
       LCD_moveCursor(0,1);
       LCD_displayString("Distance =   cm");

while(1)
	{

			Total_distance =Ultrasonic_readDistance();

			/* display the period on LCD screen */
			LCD_moveCursor(0,11);
			LCD_intgerToString(Total_distance);
		}
	}
