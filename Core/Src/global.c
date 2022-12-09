/*
 * global.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Phuc
 */

#include "global.h"

int status = INIT;
uint16_t BUTTON_PIN[NUM_BUTTONS] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin, BUTTONP_Pin};
GPIO_TypeDef * BUTTON_PORT[NUM_BUTTONS] = {GPIOA, GPIOA, GPIOB, GPIOA};
uint16_t LED_PIN[NUM_LEDS] = {LEDT1_1_Pin, LEDT1_2_Pin, LEDT2_1_Pin, LEDT2_2_Pin, LEDP_1_Pin, LEDP_2_Pin};
GPIO_TypeDef *  LED_PORT[NUM_LEDS] = {GPIOA, GPIOB, GPIOB, GPIOB, GPIOB, GPIOA};
//int timeOutLongPress[NUM_BUTTONS] = {TIMEOUT_LONG_PRESS};
int TIME_RED = 700;
int TIME_YELLOW = 200;
int TIME_GREEN = 500;
