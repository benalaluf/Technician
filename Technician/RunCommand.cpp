#include "RunCommand.h"

#include <iostream>

void RunExe(std::string command) {
    int result = WinExec(command.c_str(), SW_HIDE);
    std::cout << "WinExec result: " << result << "\n";
}
