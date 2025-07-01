#pragma once

#include <windows.h>

#define HOUR_IN_MILISECONDS  1000 * 60 * 60
#define FIVE_SECODNS_IN_MILISECONDS  1000 * 5

#define POPUP_LOOP_TEXT "MANAGMENT PROGRAM IS UP!"
#define POPUP_LOOP_CAPTION "Technician"

/*
* Creats a MessageBox popup
* 
* @param text: text to display in the messagebox
* @param caption: caption of the messagebox
*/
int PopUp(LPCSTR text, LPCSTR caption);

/*
* indecates the user the program is running with a popup,
* than sleep for an hour.
*
*/
void PopupLoop();
