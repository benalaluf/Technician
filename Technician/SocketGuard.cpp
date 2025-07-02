#include "SocketGuard.h"

#include <iostream>

#include "Exception.h"

SocketGuard::SocketGuard() {
    int iResult;

    
    iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        throw Exception(1, "WSAStartup");
    }
}

SocketGuard::~SocketGuard() {
    WSACleanup();
}
