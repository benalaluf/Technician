#pragma once

#include <windows.h>

#define RUN_KEY  "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KEY_NAME  "Technician"

/*
* Gets the current process exe path 
* 
* @param path: path to the exectuable [IN/OUT]
* @param size: length of the path [IN/OUT]
*
*/
void getProcessExe(LPSTR path, SIZE_T size);

/*
* Provide cross boot presistence using the RUN Registry key
* 
* @param path: path to the exectuable [IN]
* @param pathLength: length of the path [IN]
*
* @return exit status
*/
int RegistryLogon(LPCSTR path, SIZE_T pathLength);
