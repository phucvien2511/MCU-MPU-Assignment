/*
 * fsm.h
 *
 *  Created on: Dec 2, 2022
 *      Author: Phuc
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "global.h"

void setTrafficLight(int color1, int color2);
void fsm_automatic_run();
void fsm_manual_run();
void fsm_tuning_run();
void fsm_pedestrian_run(TIM_HandleTypeDef htim);
#endif /* INC_FSM_H_ */
