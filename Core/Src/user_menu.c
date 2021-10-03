/*
 * user_menu.c
 *
 *  Created on: Mar 13, 2021
 *      Author: bruno
 */
#include <stdbool.h>
#include "user_menu.h"
#include "distortion.h"
#include "delay.h"
#include "clean.h"

#define MENU2_SETTING_STRING_OFFSET	10
#define MENU2_edit_STRING_OFFSET	0

#define INCREMENT	true
#define DECREMENT	false

char menuClean1[16] = "Clean", menuClean2[16] = "   Level: 1";
char menuDelay1[16] = "Delay", menuDelay2[16] = "   Level: 1";
char menuDistortion1[16] = "Distortion", menuDistortion2[16] = "   Gain:  1";
char menuTuner1[16] = "Tuner", menuTuner2[16] = "   E";
char blank[16] = "                ";

typedef enum {
	MENU1 = 0,
	MENU2,
	BOTH_MENUS
}MenuRow;

typedef struct {
	Lcd_HandleTypeDef lcd;
	Menu currentMenu;
	char* menu1;
	char* menu2;
	bool isEdit;
}UserMenu;

UserMenu userMenu;

static void insertSettingInMenu(unsigned setting)
{
	sprintf((userMenu.menu2 + MENU2_SETTING_STRING_OFFSET), "%2u", setting);
}

static void updateMenuScroll(void)
{
	switch(userMenu.currentMenu) {

	case  MENU_CLEAN:
		userMenu.menu1 = menuClean1;
		userMenu.menu2 = menuClean2;
		unsigned cleanLevel = (unsigned)getCleanLevelValue();
		insertSettingInMenu(cleanLevel);
		break;

	case  MENU_DELAY:
		userMenu.menu1 = menuDelay1;
		userMenu.menu2 = menuDelay2;
		unsigned delayLevel = (unsigned)getDelayLevelValue();
		insertSettingInMenu(delayLevel);
		break;

	case  MENU_DISTORTION:
		userMenu.menu1 = menuDistortion1;
		userMenu.menu2 = menuDistortion2;
		unsigned gain = getDistortionGainValue();
		insertSettingInMenu(gain);
		break;

	case MENU_TUNER:
		userMenu.menu1 = menuTuner1;
		userMenu.menu2 = menuTuner2;

	case MENU_START:
	case MENU_END:
	default:
		break;

	}
}

static void modifySetting(bool increment, unsigned* setting)
{
	if(increment)
		*setting += 1;
	else
	{
		if(*setting <= 0)
			return;
		*setting -= 1;
	}
}

static bool updateMenuEdit(bool increment)
{
	unsigned* setting = NULL;
	bool success = false;

	switch(userMenu.currentMenu) {

	case  MENU_CLEAN:
		setting = (unsigned*)getCleanLevel();
		break;

	case  MENU_DELAY:
		setting = (unsigned*)getDelayLevel();

		break;

	case  MENU_DISTORTION:
		setting = getDistortionGain();
		break;

	case MENU_START:
	case MENU_END:
	default:
		break;
	}
	if(setting != NULL)
	{
		modifySetting(increment, setting);
		insertSettingInMenu(*setting);
		success = true;
	}

	return success;
}

static void displayMenu(MenuRow row)
{
	switch(row)	{

	case MENU1:
		Lcd_cursor(&userMenu.lcd, 0, 0);
		Lcd_string(&userMenu.lcd, userMenu.menu1);
		break;
	case MENU2:
		Lcd_cursor(&userMenu.lcd, 1, 0);
		Lcd_string(&userMenu.lcd, userMenu.menu2);
		break;
	case BOTH_MENUS:
		Lcd_clear(&userMenu.lcd);
		Lcd_cursor(&userMenu.lcd, 0, 0);
		Lcd_string(&userMenu.lcd, userMenu.menu1);
		Lcd_cursor(&userMenu.lcd, 1, 0);
		Lcd_string(&userMenu.lcd, userMenu.menu2);
		break;
	default:
		break;
	}
}

static void processEditMenu(bool increment)
{
	bool success = updateMenuEdit(increment);
	if(success)
		displayMenu(MENU2);
}

void incrementMenu(void)
{
	if(userMenu.isEdit)
		processEditMenu(INCREMENT);
	else
	{
		userMenu.currentMenu++;
		if(userMenu.currentMenu >= MENU_END)
			userMenu.currentMenu = MENU_START + 1;
		updateMenuScroll();
		displayMenu(BOTH_MENUS);
	}
}

void decrementMenu(void)
{
	if(userMenu.isEdit)
		processEditMenu(DECREMENT);
	else
	{
		userMenu.currentMenu--;
		if(userMenu.currentMenu <= MENU_START)
			userMenu.currentMenu = MENU_END - 1;
		updateMenuScroll();
		displayMenu(BOTH_MENUS);
	}
}

void toggleMenuEdit(void)
{
	if(userMenu.isEdit)
	{
		userMenu.isEdit = false;
		strncpy(userMenu.menu2, "   ", 3);
	}
	else
	{
		userMenu.isEdit = true;
		strncpy(userMenu.menu2, "-> ", 3);
	}
	displayMenu(MENU2);
}

Menu getCurrentMenu(void)
{
	return userMenu.currentMenu;
}
void initMenu(Lcd_PortType port[], Lcd_PinType pin[])
{
	userMenu.currentMenu = MENU_CLEAN;
	updateMenuScroll();
	userMenu.lcd = Lcd_create(port, pin, LCD_RS_GPIO_Port, LCD_RS_Pin, LCD_E_GPIO_Port, LCD_E_Pin, LCD_4_BIT_MODE);
	Lcd_string(&userMenu.lcd, "STM32 Effects!");
	HAL_Delay(1000);
	displayMenu(BOTH_MENUS);
}
