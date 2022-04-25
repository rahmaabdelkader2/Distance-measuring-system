/*
 * ULTRASONIC .h
 *
 *  Created on: Oct 21, 2021
 *      Author: Rahma Abdelkader
 */

#ifndef ULTRASONIC__H_
#define ULTRASONIC__H_

#include "std_types.h"

 /*   PROTOTYPES OF initialization and ULTRASONIC FUNCTIONS */

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC__H_ */
