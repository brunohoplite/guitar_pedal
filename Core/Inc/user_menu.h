/*
 * user_menu.h
 *
 *  Created on: Mar 13, 2021
 *      Author: bruno
 */

#ifndef INC_USER_MENU_H_
#define INC_USER_MENU_H_

#include "lcd.h"

typedef enum {
	MENU_START = 0,
	MENU_CLEAN = 1,
	MENU_DELAY = 2,
	MENU_DISTORTION = 3,
#ifdef FEATURE_TUNER
	MENU_TUNER = 4,
#endif

	MENU_END
}Menu;

void initMenu(Lcd_PortType port[], Lcd_PinType pin[]);
void incrementMenu(void);
void decrementMenu(void);
void toggleMenuEdit(void);
Menu getCurrentMenu(void);

#endif /* INC_USER_MENU_H_ */
