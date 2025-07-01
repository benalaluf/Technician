#include "Registry.h"

#include <iostream>

#define DATA_VALUE_BUFFER_SIZE 1024
#define MAX_RUN_VALUE_SIZE 160


LSTATUS createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
                  LPSECURITY_ATTRIBUTES securityAttributes, PHKEY result, LPDWORD disposition) {

    LSTATUS createStatus =
        RegCreateKeyExA(key, subKey, NULL, lpClass, options, samDesired, securityAttributes, result, disposition);

    std::cout << "create status: " << createStatus << "\n";

    if (key == NULL || createStatus) {
        throw KEY_HANDLE_ERROR;
    }

    return createStatus;
}

LSTATUS setValue(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    LSTATUS setStatus = RegSetValueExA(key, valueName, 0, type, data, dataSize);

    std::cout << "set status: " << setStatus << "\n";
    if (setStatus) {
        throw SET_KEY_ERROR;
    }
    return setStatus;
}

LPCSTR getValue(HKEY key) {
    DWORD dataSize = DATA_VALUE_BUFFER_SIZE;
    char* data = new char[DATA_VALUE_BUFFER_SIZE];
    LSTATUS getStatus = RegGetValueA(key, NULL, NULL, RRF_RT_ANY, NULL, data, &dataSize);

    if (getStatus == ERROR_FILE_NOT_FOUND) {
        throw KEY_NOT_FOUND_ERROR;
    }
    if (getStatus) {
        throw GET_KEY_ERROR; 
    }

    std::cout << "get status: " << getStatus << "\n";
    return data;
}

LSTATUS setValueIfNotAllReadyExsits(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    try {
        LPCSTR value = getValue(key);
        int cmpResult = strncmp(reinterpret_cast<const char*>(data), value, dataSize );
        if (!cmpResult) {
            return 0;
        }
    } catch (const RegistryError& error) {
        if (error != KEY_NOT_FOUND_ERROR) {
            throw error;
        }
    }

    setValue(key, valueName, type, data, dataSize);

    return 0;
}

std::string getRegistryError(const RegistryError& error) {
    switch (error) {
    case KEY_HANDLE_ERROR: {
        return "Key Handle Error, Error Code: " + GetLastError();
        break;
    }
    case KEY_NOT_FOUND_ERROR: {
        return "Key Not Found Error, Error Code: " + GetLastError();
        break;
    }
    case SET_KEY_ERROR: {
        return "Set Key Error, Error Code: " + GetLastError();
        break;
    }
    default: {
        return "Unkown";
    }
    }
}
