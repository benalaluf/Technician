#include "Socket.h"

#include <vector>
#include <string>

#include "Exception.h"

#define DEFAULT_PORT "1337"
#define REQUEST_STRING "PING"
#define RESPONSE_STRING "PONG"

class AgentException : public Exception {
  public:
    SOCKET m_socket;
    AgentException(int status, std::string funcName, SOCKET sock);
};

class Agent {
    Socket m_conn;
    struct addrinfo *m_addr;
  public:
    Agent();
    void initSocket();
    void start();
    void handleClient();
    void agentSend(Socket sock, std::string message);

};
