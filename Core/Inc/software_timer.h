/*
 * software_timer.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Phuc
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#include "global.h"
void setTimer(int index, int duration);
void deleteTimer(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
