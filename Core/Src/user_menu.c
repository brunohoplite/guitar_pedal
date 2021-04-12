/*
 * user_menu.c
 *
 *  Created on: Mar 13, 2021
 *      Author: bruno
 */

#include "user_menu.h"
#include "lcd.h"

Lcd_PortType ports[] = {
		LCD_D4_GPIO_Port, LCD_D5_GPIO_Port, LCD_D6_GPIO_Port, LCD_D7_GPIO_Port
};

Lcd_PinType pins[] = {LCD_D4_Pin, LCD_D5_Pin, LCD_D6_Pin, LCD_D7_Pin};

Lcd_HandleTypeDef lcd;

Menu currentMenu = MENU_CLEAN;
char menuClean[16] = "Clean", menuDelay[16] = "Delay", menuDistortion[16] = "Distortion";

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
	lcd = Lcd_create(ports, pins, LCD_RS_GPIO_Port, LCD_RS_Pin, LCD_E_GPIO_Port, LCD_E_Pin, LCD_4_BIT_MODE);
	Lcd_string(&lcd, "STM32 Effects!");
	HAL_Delay(1000);
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
