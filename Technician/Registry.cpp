#include "Registry.h"

#include <iostream>

#define DATA_VALUE_BUFFER_SIZE 1024
#define MAX_RUN_VALUE_SIZE 160

HKEY createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
               LPSECURITY_ATTRIBUTES securityAttributes, LPDWORD disposition) {
    HKEY result;
    LSTATUS createStatus =
        RegCreateKeyExA(key, subKey, NULL, lpClass, options, samDesired, securityAttributes, &result, disposition);

    if (result == NULL || createStatus) {
        throw RegistryException(createStatus, "RegCreateKeyExA");
    }

    return result;
}

void setValue(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    LSTATUS setStatus = RegSetValueExA(key, valueName, 0, type, data, dataSize);

    if (setStatus) {
        throw RegistryException(setStatus, "RegSetValueExA");
    }
}

std::string getValue(HKEY key) {
    DWORD dataSize = DATA_VALUE_BUFFER_SIZE;
    char data[DATA_VALUE_BUFFER_SIZE];
    LSTATUS getStatus = RegGetValueA(key, NULL, NULL, RRF_RT_ANY, NULL, data, &dataSize);

    if (getStatus) {
        throw RegistryException(getStatus, "RegGetValueA");
    }

    return std::string(data);
}

void setValueIfNotAllReadyExsits(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    try {
        std::string value = getValue(key);
        int cmpResult = strncmp(reinterpret_cast<const char*>(data), value.c_str(), dataSize);
        if (!cmpResult) {
            return;
        }
    } catch (const RegistryException& error) {
        if (error.status != ERROR_FILE_NOT_FOUND) {
            throw error;
        }
    }

    setValue(key, valueName, type, data, dataSize);
}

RegistryException::RegistryException(int status, std::string funcName) : Exception(status, funcName) {
    // intatinly empty
}
