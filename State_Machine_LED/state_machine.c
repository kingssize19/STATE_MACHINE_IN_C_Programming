/*
 * state_machine.c
 *
 *  Created on: Oct 13, 2024
 *      Author: hayat
 */

#include "state_machine.h"

extern int clock_counter;
State_Type current_state;

void (*state_table[])(void) = {//state_machine_init,
							   state_LED1,
							   state_LED2,
							   state_LED3,
							   state_LED4,
};

void state_machine_init(void) {
	current_state = STATE_LED1;
	clock_counter = 0;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
}

void state_LED1(void) {
	if (clock_counter == 1) {
		current_state = STATE_LED2;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	}
}

void state_LED2(void) {
	if (clock_counter == 2) {
		current_state = STATE_LED3;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	}
}

void state_LED3(void) {
	if (clock_counter == 3) {
		current_state = STATE_LED4;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	}
}

void state_LED4(void) {
	if (clock_counter == 4) {
		current_state = STATE_LED1;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
		clock_counter = 0;
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
	}
}


