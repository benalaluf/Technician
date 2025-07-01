#pragma once

#include <windows.h>

#define HOUR_IN_MILISECONDS  1000 * 60 * 60
#define FIVE_SECODNS_IN_MILISECONDS  1000 * 5

int PopUp(LPCSTR text, LPCSTR caption);

void PopupLoop();
