#pragma once

#include <WinSock2.h>
#include <Windows.h>

#define DEFAULT_PORT "1337"

class Agent {
  public:
    void createSocket();
    void handleClient();
};
