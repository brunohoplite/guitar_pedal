/*
 * user_menu.c
 *
 *  Created on: Mar 13, 2021
 *      Author: bruno
 */

#include "user_menu.h"
#include "lcd.h"

Menu currentMenu = MENU_CLEAN;
char menuClean[16] = "Clean", menuDelay[16] = "Delay", menuDistortion[16] = "Distortion";
extern Lcd_HandleTypeDef lcd;

static void displayMenu(void)
{
	char* menu;

	switch(currentMenu) {

	case  MENU_CLEAN:
		menu = menuClean;
		break;

	case  MENU_DELAY:
		menu = menuDelay;
		break;

	case  MENU_DISTORTION:
		menu = menuDistortion;
		break;

	case MENU_START:
	case MENU_END:
	default:
		break;

	}
	Lcd_cursor(&lcd, 1, 0);
	Lcd_clear(&lcd);
	Lcd_string(&lcd, menu);
}

void initMenu(void)
{
	displayMenu();
}

void incrementMenu(void)
{
	currentMenu++;
	if(currentMenu >= MENU_END)
		currentMenu = MENU_CLEAN;
	displayMenu();
}

void decrementMenu(void)
{
	currentMenu--;
	if(currentMenu <= MENU_START)
		currentMenu = MENU_DISTORTION;
	displayMenu();
}

Menu getCurrentMenu(void)
{
	return currentMenu;
}
