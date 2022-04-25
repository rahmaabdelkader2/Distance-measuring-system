/*
 * ULTRASONIC .c
 *
 *  Created on: Oct 21, 2021
 *      Author: Rahma Abdelkader
 */
#include "ULTRASONIC.h"
#include "gpio.h"
#include "ICU.h"
#include <avr/delay.h>
#include "std_types.h"

     uint8 g_edgeCount = 0;
	 uint16 g_timeHigh = 0;



/* initialize ultrasonic */

void Ultrasonic_init(void){

	// pasing 8 clock , rising edge

	  Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
      Icu_init(&Icu_Config);

      //call back function

	  Icu_setCallBack(Ultrasonic_edgeProcessing);

	  GPIO_setupPinDirection(PORTD_ID , PIN5_ID , PIN_OUTPUT);
	  GPIO_writePin(PORTD_ID, PIN5_ID , LOGIC_LOW);
}

/* sending pulse */

void Ultrasonic_Trigger(void){

	 GPIO_writePin(PORTB_ID , PIN5_ID , LOGIC_HIGH);
     _delay_us(10);
	 GPIO_writePin(PORTB_ID , PIN5_ID , LOGIC_LOW);
}

/* function to read distance in cm */

uint16 Ultrasonic_readDistance(void){

	 Ultrasonic_Trigger();


 return (g_timeHigh/58.8);

}


void Ultrasonic_edgeProcessing(void){




	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount=0;
	}


	}

