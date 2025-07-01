#include "Registry.h"

#include <iostream>

#define DATA_VALUE_BUFFER_SIZE 1024

LSTATUS createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
                  LPSECURITY_ATTRIBUTES securityAttributes, PHKEY result, LPDWORD disposition) {

    LSTATUS createStatus =
        RegCreateKeyExA(key, subKey, NULL, lpClass, options, samDesired, securityAttributes, result, disposition);

    std::cout << "create status: " << createStatus << "\n";

    if (key == NULL) {
        throw KEY_HANDLE_ERROR;
    }

    return createStatus;
}

LSTATUS setKey(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    LSTATUS setStatus = RegSetValueExA(key, valueName, 0, type, data, dataSize);

    std::cout << "set status: " << setStatus << "\n";
    if (setStatus) {
        throw SET_KEY_ERROR;
    }
    return setStatus;
}

LSTATUS getKey(HKEY key, LPCSTR valueName, DWORD flags, LPDWORD type, PVOID data, LPDWORD dataSize) {
    LSTATUS getStatus = RegGetValueA(key, NULL, valueName, flags, type, data, dataSize);
    if (getStatus == ERROR_FILE_NOT_FOUND) {
        throw KEY_NOT_FOUND_ERROR;
    }
    std::cout << "get status: " << getStatus << "\n";
    return getStatus;
}

LSTATUS setKeyIfNotAllReadyExsits(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    DWORD bufferDataSize = DATA_VALUE_BUFFER_SIZE;
    BYTE bufferData[DATA_VALUE_BUFFER_SIZE];

    try {
        LSTATUS queryStatus = getKey(key, valueName, RRF_RT_ANY, NULL, bufferData, &bufferDataSize);
        int cmpResult = memcmp(data, bufferData, bufferDataSize);
        if (!cmpResult) {
            return 0;
        }
    } catch (const RegistryError& error) {
        if (error != KEY_NOT_FOUND_ERROR) {
            throw error;
        }
    }

    setKey(key, valueName, type, data, dataSize);

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
