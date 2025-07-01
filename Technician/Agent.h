#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "1337"

class Agent {
    SOCKET m_conn;
    struct addrinfo *m_addr;
  public:
    Agent();
    void initSocket();
    void start();
    void bindSocket();
    void listenSocket();
    void handleClient();
};
