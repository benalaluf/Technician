#include "Registry.h"

#include <iostream>

#define DATA_VALUE_BUFFER_SIZE 1024 

LSTATUS createKey(HKEY key, LPCSTR subKey, LPSTR lpClass, DWORD options, REGSAM samDesired,
                  LPSECURITY_ATTRIBUTES securityAttributes, PHKEY result, LPDWORD disposition) {

    LSTATUS createStatus =
        RegCreateKeyExA(key, subKey, NULL, lpClass, options, samDesired, securityAttributes, result, disposition);

    std::cout << "create status: " << createStatus;

    if (key == NULL) {
        throw KEY_HANDLE_ERROR;
    }
}

LSTATUS setKey(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    LSTATUS setStatus = RegSetValueExA(key, valueName, 0, type, data, dataSize);
    if (!setStatus) {
        std::cerr << "RegSetValue Failed status: " << setStatus << "\n";
    }

    return setStatus;
}

LSTATUS setKeyIfNotAllReadyExsits(HKEY key, LPCSTR valueName, DWORD type, const BYTE* data, DWORD dataSize) {
    DWORD bufferDataSize = DATA_VALUE_BUFFER_SIZE;
    BYTE bufferData[DATA_VALUE_BUFFER_SIZE];

    LSTATUS queryStatus =
        RegGetValueA(key, NULL, valueName, RRF_RT_ANY, NULL, reinterpret_cast<BYTE*>(bufferData), &bufferDataSize);

    int cmpResult = memcmp(data, bufferData, bufferDataSize);
    std::cout << "query status: " << queryStatus;

    if (queryStatus == ERROR_FILE_NOT_FOUND || cmpResult != 0) {
        setKey(key, valueName, type, data, dataSize);
    }

    return 0;
}
    std::string getRegistryError(const RegistryError& error) {
        switch (error) {
        case KEY_HANDLE_ERROR: {
            return "Key Handle Error, Error Code: " + GetLastError();
            break;
        }
        default: {
            return "Unkown";
        }
        }
    }
