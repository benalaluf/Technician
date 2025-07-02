#include "RunCommand.h"

#include <iostream>

void RunExe(std::string path) {
    int result = WinExec(path.c_str(), SW_SHOW);
    std::cout << "WinExec result: " << result << "\n";
}
