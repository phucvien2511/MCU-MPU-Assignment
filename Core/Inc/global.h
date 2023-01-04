/*
 * global.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Phuc
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "button.h"

/* Pins amount define */
#define NUM_BUTTONS		4		//Button pin amount
#define NUM_LEDS		6		//Single LED pin amount
#define NUM_TIMERS		4		//Timer amount
/* Pins amount define END */

/* FSM states define */
#define INIT			10
#define RG				11
#define RY				12
#define GR				13
#define YR				14
#define MAN_RED			15
#define MAN_YELLOW1		16
#define MAN_YELLOW2		17
#define MAN_GREEN		18
#define SET_RED			19
#define SET_YELLOW		20
#define P_INIT			21
#define P_RED			22
#define P_YELLOW		23
#define P_GREEN			24
#define IDLE			25
/* FSM states define END */
/* UART FSM define */
#define UART_INIT		40
#define UART_SEND		41
#define UART_WAIT		42
#define UART_OK			43
/* UART FSM define END */
/* Other define */
#define TIMEOUT_LONG_PRESS	300
#define RED					30
#define YELLOW				31
#define GREEN				32
#define OFF					33
#define MAX_BUFFER_SIZE		30
/* Other define END */

/* Global variables */
extern int status;						//FSM status
extern int p_status;				//Pedestrian light status
GPIO_TypeDef * BUTTON_PORT[NUM_BUTTONS];
uint16_t BUTTON_PIN[NUM_BUTTONS];
GPIO_TypeDef * LED_PORT[NUM_LEDS];
uint16_t LED_PIN[NUM_LEDS];
extern int button_flag[NUM_BUTTONS];
extern int TIME_RED;
extern int TIME_YELLOW;
extern int TIME_GREEN;
extern int timeOutForLongPress[NUM_BUTTONS];
extern int timer_flag[NUM_TIMERS];
extern int timer_counter[NUM_TIMERS];
extern uint8_t buffer_bytes;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t buffer_flag;
extern char str[50];
//extern int timer_counter[NUM_TIMERS];
//extern int timer_flag[NUM_TIMERS];
/* Global variables END */

#endif /* INC_GLOBAL_H_ */
