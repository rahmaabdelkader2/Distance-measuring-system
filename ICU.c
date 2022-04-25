/*
 * ICU.c
 *
 *  Created on: Oct 20, 2021
 *      Author: Rahma abdelkader
 */
/******************************************************************************/


#include "gpio.h"
#include "icu.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void Icu_init(const Icu_ConfigType * Config_Ptr)
{


	GPIO_setupPinDirection(PORTD_ID , PIN6_ID , PIN_INPUT); // Configure ICP1/PD6 AS INPUT

	TCCR1A = (1<<FOC1A) | (1<<FOC1B); //normal mode for timer1

	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);//clock in 3 bits ( CS10,CS11,CS12) in TCCR1B

	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6); // edge in bit TCCR1B

	TCNT1 = 0; //intial value for TIMER1


	ICR1 = 0;//Intial value for input capture register


	TIMSK |= (1<<TICIE1); //enable input capture interrupt when edge  is detected on PD6 to generate interrupt
}

/*
 * Description: Function to set the Call Back function address.
 */
void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(const Icu_EdgeType a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}


