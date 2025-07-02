#include "CreateProcess.h"

#include <Windows.h>
#include <iostream>

void MyCreateProcess(std::string path) {
    STARTUPINFOA info{};
    PROCESS_INFORMATION procinfo{};
    BOOL result = CreateProcessA(path.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &info, &procinfo);
    std::cout << "CreateProcess: " << path << "Result: " << result << GetLastError() << "\n";
}
