/*
 * fsm.c
 *
 *  Created on: Dec 2, 2022
 *      Author: Phuc
 */

#include "fsm.h"

void setTrafficLight(int color1, int color2) {
	switch (color1) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 1);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 0);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 1);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 0);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 1);
		break;
	default:
		break;
	}
	switch (color2) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 1);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 0);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 1);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 0);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 1);
		break;
	default:
		break;
	}
}

void fsm_automatic_run() {
	switch (status) {
	case INIT:
		setTimer(0, TIME_RED);		//1st route is red
		setTimer(1, TIME_GREEN);	//2nd route is green
		status = RG;
		break;
	case RG:
		setTrafficLight(RED, GREEN);
		if (isButtonPressed[0]) {
			status = MAN_RED;
		}
		if (timer_counter[1] == 0) {
			setTimer(1, TIME_YELLOW);
			status = RY;
		}
		break;
	case RY:
		setTrafficLight(RED, YELLOW);
		if (isButtonPressed[0]) {
			status = MAN_RED;
		}
		if (timer_counter[0] == 0 && timer_counter[1] == 0) {
			setTimer(0, TIME_GREEN);
			setTimer(1, TIME_RED);
			status = GR;
		}
		break;
	case GR:
		setTrafficLight(GREEN, RED);
		if (isButtonPressed[0]) {
			status = MAN_RED;
		}
		if (timer_counter[0] == 0) {
			setTimer(0, TIME_YELLOW);
			status = YR;
		}
		break;
	case YR:
		setTrafficLight(YELLOW, RED);
		if (isButtonPressed[0]) {
			status = MAN_RED;
		}
		if (timer_counter[0] == 0 && timer_counter[1] == 0) {
			setTimer(0, TIME_RED);
			setTimer(1, TIME_GREEN);
			status = RG;
		}
		break;
}

void fsm_manual_run() {
	switch (status) {
	case MAN_RED:
		setTrafficLight(RED, GREEN);
		if (isButtonPressed[0]) {
			status = MAN_YELLOW1;
			setTimer(0, 500);
		}
		break;
	case MAN_YELLOW1:
		setTrafficLight(RED, YELLOW);
		if (timer_counter[0] == 0) {	//Yellow light time was ended
			status = MAN_GREEN;
		}
		break;
	case MAN_GREEN:
		setTrafficLight(GREEN, RED);
		if (isButtonPressed[0]) {
			status = MAN_YELLOW2;
			setTimer(1, 500);
		}
		break;
	case MAN_YELLOW2:
		setTrafficLight(YELLOW, RED);
		if (timer_counter[0] == 0) {	//Yellow light time was ended
			status = MAN_RED;
		}
		break;
	}
}

void fsm_tuning_run() {
	switch (status) {
	case SET_RED:
		break;
	case SET_YELLOW:
		break;
	}
}
