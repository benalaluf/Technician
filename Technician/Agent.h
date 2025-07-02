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

#define DEFAULT_PORT "1337"
#define DEFAULT_BUFLEN 512
#define REQUEST_STRING "PING"
#define RESPONSE_STRING "PONG"

class AgentException : public Exception {
  public:
    SOCKET m_socket;
    AgentException(int status, std::string funcName, SOCKET sock);
};

class Agent {
    SOCKET m_conn;
    struct addrinfo *m_addr;
  public:
    Agent();
    void initSocket();
    void start();
    void bindSocket();
    void listenSocket();
    SOCKET agentAccept();
    void handleClient();
    void agentSend(SOCKET sock, char* data, size_t dataSize);
    void agentSend(SOCKET sock, std::string message);
    std::vector<char> agentRecv(SOCKET sock);

};
