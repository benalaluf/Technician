#pragma once

#include <windows.h>

#define RUN_KEY  "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KEY_NAME  "Technician"

void getProcessExe(LPSTR path, SIZE_T size);

int RegistryLogon(LPCSTR path, SIZE_T pathLength);
