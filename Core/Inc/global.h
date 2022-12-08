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
#define SET_GREEN		21
/* FSM states define END */

/* Other define */
#define TIMEOUT_LONG_PRESS	300
#define RED					30
#define YELLOW				31
#define GREEN				32
/* Other define END */

/* Global variables */
extern int status;						//FSM status
uint16_t BUTTON_PIN[NUM_BUTTONS];
uint16_t BUTTON_PORT[NUM_BUTTONS];
uint16_t LED_PIN[NUM_LEDS];
uint16_t LED_PORT[NUM_LEDS];
extern int button_flag[NUM_BUTTONS];
extern int TIME_RED;
extern int TIME_YELLOW;
extern int TIME_GREEN;
extern int timer_counter[NUM_TIMERS];
/* Global variables END */

#endif /* INC_GLOBAL_H_ */
