#pragma once

#include <string>
#include <windows.h>

enum RegistryError
{
    KEY_HANDLE_ERROR,
    KEY_NOT_FOUND_ERROR,
    SET_KEY_ERROR,
};

std::string getRegistryError(const RegistryError& error);

LSTATUS createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
                  LPSECURITY_ATTRIBUTES securityAttributes, PHKEY result, LPDWORD disposition);

LSTATUS getKey(HKEY key, LPCSTR valueName, DWORD flags, LPDWORD type, PVOID data, LPDWORD dataSize);

LSTATUS setKeyIfNotAllReadyExsits(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize);
