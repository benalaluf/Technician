#include "RunCommand.h"

#include <iostream>

void RunExe(std::string command) {
    int result = WinExec(command.c_str(), SW_SHOW);
    std::cout << "WinExec result: " << result << "\n";
}
