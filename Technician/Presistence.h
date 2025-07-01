#pragma once

#include <windows.h>

#define RUN_KEY  "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KEY_NAME  "Technician"

int RegistryLogon(LPCSTR path, SIZE_T pathLength);
