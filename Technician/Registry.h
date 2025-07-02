#pragma once

#include <string>
#include <windows.h>

#include "Exception.h"

/*
 * Defines Errors for the Registry module.
 */
class RegistryException : public Exception {
  public:
    RegistryException(int status, std::string funcName);
};

/*
 * Wraps RegCreateKeyExA
 */
HKEY createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
               LPSECURITY_ATTRIBUTES securityAttributes, LPDWORD disposition);

/*
 * Wraps RegSetValueExA
 */
void setValue(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize);

void setValue(HKEY key, LPCSTR valueName, std::string value);

/*
 * Wraps RegGetValueA
 */
void getValue(HKEY key, BYTE* data, LPDWORD dataSize);
std::string getValue(HKEY key);

/*
 * Use set only if the key dosent allready exsits or its value isnt right.
 */
void setValueIfNotAllReadyExsits(HKEY key, LPCSTR valueName, std::string newValue);
