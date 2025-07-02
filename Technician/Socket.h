#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#include <vector>
#include <string>

#include "Exception.h"


class SocketException : public Exception {
  public:
    SOCKET m_socket;
    SocketException(int status, std::string funcName, SOCKET sock);
};

class Socket {
    SOCKET m_sock;
  public:
    Socket();
    Socket(struct addrinfo* addr);
    Socket(SOCKET sock);
    void bind(struct addrinfo* addr);
    void connect();
    void listen();
    Socket accept();
    void send(char* data, size_t dataSize);
    std::vector<char> recv(size_t size);

};
    
struct addrinfo* createAddress(std::string port);
