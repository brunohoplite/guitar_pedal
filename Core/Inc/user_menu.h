/*
 * user_menu.h
 *
 *  Created on: Mar 13, 2021
 *      Author: bruno
 */

#ifndef INC_USER_MENU_H_
#define INC_USER_MENU_H_

typedef enum {
	MENU_START = 0,
	MENU_CLEAN,
	MENU_DELAY,
	MENU_DISTORTION,

	MENU_END
}Menu;

void initMenu(void);
void incrementMenu(void);
void decrementMenu(void);
Menu getCurrentMenu(void);

#endif /* INC_USER_MENU_H_ */
