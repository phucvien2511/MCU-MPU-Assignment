/*
 * fsm.c
 *
 *  Created on: Dec 2, 2022
 *      Author: Phuc
 */

#include "fsm.h"
#include <stdio.h>
int temp_time = 1;
int volume = 0;
int buzzer_delay = 1000;
int delay_ratio = 0, volume_ratio = 0;
UART_HandleTypeDef huart2;
void setTrafficLight(int color1, int color2) {
	switch (color1) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 0);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 1);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 1);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[0], LED_PIN[0], 1);
		HAL_GPIO_WritePin(LED_PORT[1], LED_PIN[1], 0);
		break;
	default:
		break;
	}
	switch (color2) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 0);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 1);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 1);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[2], LED_PIN[2], 1);
		HAL_GPIO_WritePin(LED_PORT[3], LED_PIN[3], 0);
		break;
	default:
		break;
	}
}
void setPedesLight(int color) {
	switch (color) {
	case RED:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 0);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 1);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 1);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 1);
		break;
	case GREEN:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 1);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 0);
		break;
	case OFF:
		HAL_GPIO_WritePin(LED_PORT[4], LED_PIN[4], 0);
		HAL_GPIO_WritePin(LED_PORT[5], LED_PIN[5], 0);
		break;
	default:
		break;
	}

}

void setBuzzer(TIM_HandleTypeDef htim) {
	__HAL_TIM_SetCompare(&htim, TIM_CHANNEL_1, volume);
	HAL_Delay(buzzer_delay);
	__HAL_TIM_SetCompare(&htim, TIM_CHANNEL_1, 0);
	HAL_Delay(buzzer_delay);
	volume += volume_ratio;
	if (volume > 1000) volume = volume_ratio;
	buzzer_delay -= delay_ratio;
	if (buzzer_delay < 1) buzzer_delay = 1000;
}

void send7SEG(int TIME) {
	sprintf(str, "!7SEG:%d%d#\r\n", TIME/10, TIME%10);
	HAL_UART_Transmit_IT(&huart2, (void*)str, 100);
}
void fsm_automatic_run() {
	switch (status) {
	case INIT:
		setTimer(0, TIME_RED);		//1st route is red
		setTimer(1, TIME_GREEN);	//2nd route is green
		status = RG;
		break;
	case RG:
		send7SEG(TIME_RED);
		setTrafficLight(RED, GREEN);
		if (timer_flag[1] == 1) {
			setTimer(1, TIME_YELLOW);
			status = RY;
		}
		if (isButtonPressed(1)) {
			status = MAN_RED;
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		if (isButtonPressed(3)) {
			p_status = P_INIT;
		}
		break;
	case RY:
		send7SEG(TIME_RED);
		setTrafficLight(RED, YELLOW);
		if (timer_flag[1] == 1) {
			setTimer(0, TIME_GREEN);
			setTimer(1, TIME_RED);
			status = GR;
		}
		if (isButtonPressed(1)) {
			status = MAN_RED;
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		if (isButtonPressed(3)) {
			p_status = P_INIT;
		}
		break;
	case GR:
		send7SEG(TIME_GREEN);
		setTrafficLight(GREEN, RED);
		if (timer_flag[0] == 1) {
			setTimer(0, TIME_YELLOW);
			status = YR;
		}
		if (isButtonPressed(1)) {
			status = MAN_RED;
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		if (isButtonPressed(3)) {
			p_status = P_INIT;
		}
		break;
	case YR:
		send7SEG(TIME_YELLOW);
		setTrafficLight(YELLOW, RED);
		if (timer_flag[0] == 1) {
			setTimer(0, TIME_RED);
			setTimer(1, TIME_GREEN);
			status = RG;
		}
		if (isButtonPressed(1)) {
			status = MAN_RED;
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		if (isButtonPressed(3)) {
			p_status = P_INIT;
		}
		break;
	default:
		break;
	}
}

void fsm_manual_run() {
	switch (status) {
	case MAN_RED:
		setTrafficLight(RED, GREEN);
		if (isButtonPressed(0)) {
			status = MAN_YELLOW1;
			setTimer(0, 300);
		}
		if (isButtonPressed(1)) {
			status = RG;
			setTimer(0, TIME_RED);
			setTimer(1, TIME_GREEN);
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		break;
	case MAN_YELLOW1:
		setTrafficLight(RED, YELLOW);
		if (timer_flag[0] == 1) {	//Yellow light time was ended
			status = MAN_GREEN;
		}
		if (isButtonPressed(1)) {
			status = RY;
			setTimer(0, TIME_RED);
			setTimer(1, TIME_YELLOW);
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		break;
	case MAN_GREEN:
		setTrafficLight(GREEN, RED);
		if (isButtonPressed(0)) {
			status = MAN_YELLOW2;
			setTimer(0, 300);
		}
		if (isButtonPressed(1)) {
			status = GR;
			setTimer(0, TIME_GREEN);
			setTimer(1, TIME_RED);
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		break;
	case MAN_YELLOW2:
		setTrafficLight(YELLOW, RED);
		if (timer_flag[0] == 1) {	//Yellow light time was ended
			status = MAN_RED;
		}
		if (isButtonPressed(1)) {
			status = YR;
			setTimer(0, TIME_YELLOW);
			setTimer(1, TIME_RED);
		}
		if (isButtonPressed(2)) {
			status = SET_RED;
			setTimer(2, 1000);
		}
		break;
	default:
		break;
	}
}

void fsm_tuning_run() {
	switch (status) {
	case SET_RED:
		setTrafficLight(RED, RED);
		if (timer_flag[2] == 1) {
			status = INIT;
			deleteTimer(2);
		}
		if (isButtonPressed(0)) {
			temp_time++;
			if (temp_time > 99) temp_time = 1;
			setTimer(2, 1000);
		}
		if (isButtonPressed(1)) {
			temp_time--;
			if (temp_time < 1) temp_time = 99;
			setTimer(2, 1000);
		}
		if (isButtonPressed(2)) {
			TIME_RED = temp_time*100;
			temp_time = 1;
			status = SET_YELLOW;
			setTimer(2, 1000);
		}
		break;
	case SET_YELLOW:
		setTrafficLight(YELLOW, YELLOW);
		if (timer_flag[2] == 1) {
			status = RG;
			deleteTimer(2);
		}
		if (isButtonPressed(0)) {
			temp_time++;
			if (temp_time > 99) temp_time = 1;
			setTimer(2, 1000);
		}
		if (isButtonPressed(1)) {
			temp_time--;
			if (temp_time < 1) temp_time = 99;
			setTimer(2, 1000);
		}
		if (isButtonPressed(2)) {
			TIME_YELLOW = temp_time*100;
			TIME_GREEN = TIME_RED - TIME_YELLOW;
			temp_time = 1;
			status = INIT;
			deleteTimer(2);
		}
		break;
	default:
		break;
	}
}

void fsm_pedestrian_run(TIM_HandleTypeDef htim) {
	switch (p_status) {
	case IDLE:	//Wait until pedes button pressed/road 1 light is red
		setPedesLight(OFF);
		volume = 0;
		break;
	case P_INIT:
	//Route 1
		//Red
		if (status == RG || status == RY) {
			//setTimer(3, TIME_RED - timer_counter[0]);	//Pedes light color = green until traffic light is not RED
			p_status = P_GREEN;
			delay_ratio = 1000/(timer_counter[0]/100);
			volume_ratio = 1000/(timer_counter[0]/100);
			volume = 0;
			buzzer_delay = 1000;
		}
		//Green
		else if (status == GR || status == YR) {
			//Pedes light color = red => Turn off
			p_status = P_RED;
			delay_ratio = 0;
			volume_ratio = 0;
			volume = 0;
			buzzer_delay = 0;
		}
		break;
	case P_RED:	//Pedestrian off
		setPedesLight(RED);
		//setBuzzer(htim);
		volume = 0;
		if (isButtonPressed(3)) {
			status = INIT;
		}
		if (status == RG || status == RY) {
			p_status = P_GREEN;
			setTimer(3, TIME_GREEN);
			delay_ratio = 1000/(timer_counter[0]/100);
			volume_ratio = 1000/(timer_counter[0]/100);
			volume = 0;
			buzzer_delay = 1000;
		}
		break;
	case P_GREEN:	//Pedestrian on
		setPedesLight(GREEN);
		setBuzzer(htim);
		if (isButtonPressed(0)) {
			status = INIT;
			volume = 0;
		}
		if (status == YR || status == GR) {
			p_status = IDLE;
		}
		break;
	default:

		break;

	}
}


