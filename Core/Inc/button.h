/*
 * button.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Phuc
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define		NORMAL_STATE 	GPIO_PIN_SET
#define 	PRESSED_STATE 	GPIO_PIN_RESET

int isButtonPressed(int i);
int isButtonLongPressed(int i);
void getKeyInput();


#endif /* INC_BUTTON_H_ */
