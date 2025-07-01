#pragma once

#include <windows.h>

#define HOUR_IN_MILISECONDS  1000 * 60 * 60
#define FIVE_SECODNS_IN_MILISECONDS  1000 * 5

#define POPUP_LOOP_TEXT "MANAGMENT PROGRAM IS UP!"
#define POPUP_LOOP_CAPTION "Technician"

int PopUp(LPCSTR text, LPCSTR caption);

void PopupLoop();
