#include "Presistence.h"

#include <iostream>

#include <windows.h>

#include "Registry.h"

std::string getProcessExe() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    return std::string(path);
}

void RegistryLogon(std::string path) {
    std::cout << path << "\n";
    try {
        HKEY key = createKey(HKEY_CURRENT_USER, RUN_KEY, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, NULL);

        const BYTE* pathBytes = reinterpret_cast<const BYTE*>(path.c_str());
        setValueIfNotAllReadyExsits(key, KEY_NAME, REG_SZ, pathBytes, path.size());
        CloseHandle(key);

    } catch (const RegistryException& error) {
        std::cerr << "Error: " << error.funcName << "status code: " << error.status << "\n";
        throw PresistenceException(1, "RegistryLogon");
    }
}


PresistenceException::PresistenceException(int status, std::string funcName) : Exception(status, funcName) {
    // intatinly empty
}
