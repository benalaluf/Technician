#pragma once

#include <string>
#include <windows.h>

/*
* Defines Errors for the Registry module.
*/
enum RegistryError
{
    KEY_HANDLE_ERROR,
    KEY_NOT_FOUND_ERROR,
    SET_KEY_ERROR,
    GET_KEY_ERROR,
};

std::string getRegistryError(const RegistryError& error);

/*
* Wraps RegCreateKeyExA
*/
LSTATUS createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
                  LPSECURITY_ATTRIBUTES securityAttributes, PHKEY result, LPDWORD disposition);

/*
* Wraps RegSetValueExA
*/
LSTATUS setValue(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize);

/*
* Wraps RegGetValueA
*/
LPCSTR getValue(HKEY key);

/*
* Use set only if the key dosent allready exsits or its value isnt right. 
*/
LSTATUS setValueIfNotAllReadyExsits(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize);
