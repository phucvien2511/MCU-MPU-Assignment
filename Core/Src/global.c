/*
 * global.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Phuc
 */

#include "global.h"

int status = INIT;
int p_status = IDLE;
GPIO_TypeDef *BUTTON_PORT[NUM_BUTTONS] = {BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port, BUTTONP_GPIO_Port};
uint16_t BUTTON_PIN[NUM_BUTTONS] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin, BUTTONP_Pin};
//uint16_t LED_PIN[NUM_LEDS] = {LEDT1_1_Pin, LEDT1_2_Pin, LEDT2_1_Pin, LEDT2_2_Pin, LEDP_1_Pin, LEDP_2_Pin}; Old board
GPIO_TypeDef *LED_PORT[NUM_LEDS] = {LEDT1_1_GPIO_Port, LEDT1_2_GPIO_Port, LEDT2_1_GPIO_Port, LEDT2_2_GPIO_Port, LEDP_1_GPIO_Port, LEDP_2_GPIO_Port};
//GPIO_TypeDef *  LED_PORT[NUM_LEDS] = {GPIOA, GPIOB, GPIOB, GPIOB, GPIOB, GPIOA}; Old board
uint16_t  LED_PIN[NUM_LEDS] = {LEDT1_1_Pin, LEDT1_2_Pin, LEDT2_1_Pin, LEDT2_2_Pin, LEDP_1_Pin, LEDP_2_Pin};
//int timeOutLongPress[NUM_BUTTONS] = {TIMEOUT_LONG_PRESS};
int TIME_RED = 1500;
int TIME_YELLOW = 400;
int TIME_GREEN = 1100;
int timer_flag[NUM_TIMERS] = { 0 };
int timer_counter[NUM_TIMERS] = { 0 };
int timeOutForLongPress[NUM_BUTTONS] = {300};
char str[50];
