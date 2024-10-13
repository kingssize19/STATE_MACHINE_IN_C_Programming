/*
 * state_machine.h
 *
 *  Created on: Oct 13, 2024
 *      Author: hayat
 */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

#include "main.h"


typedef enum {
	STATE_LED1 = 0,
	STATE_LED2,
	STATE_LED3,
	STATE_LED4
}State_Type;

void state_machine_init(void);
void state_LED1(void);
void state_LED2(void);
void state_LED3(void);
void state_LED4(void);


;


#endif /* INC_STATE_MACHINE_H_ */
