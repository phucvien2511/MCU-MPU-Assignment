/*
 * button.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Phuc
 */

#include "button.h"

int KeyReg0[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_BUTTONS] = {NORMAL_STATE};
int button_flag[NUM_BUTTONS] = {0};
int buttonLongPress_flag[NUM_BUTTONS] = {0};
int timeOutLongPress[NUM_BUTTONS] = { 300 };
int isButtonPressed(int i) {
	if (button_flag[i] == 1) {
		button_flag[i] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int i) {
	if (buttonLongPress_flag[i] == 1) {
		buttonLongPress_flag[i] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput() {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);
		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg3[i] != KeyReg2[i]) {	//Normal press
				  KeyReg3[i] = KeyReg2[i];
				  if (KeyReg2[i] == PRESSED_STATE) {
					  button_flag[i] = 1;
					  timeOutLongPress[i] = TIMEOUT_LONG_PRESS;
				  }
				  //else firstLongPress = 0;
			}
			else {
				timeOutLongPress[i]--;
				if (timeOutLongPress[i] <= 0 && KeyReg2[i] == PRESSED_STATE) {	//Passed the long press timer
					KeyReg3[i] = NORMAL_STATE;
					buttonLongPress_flag[i] = 1;

				}
			}
		}
	}
}
