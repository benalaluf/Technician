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

#include "Socket.h"


#define MAX_PACKET_SIZE 1024

#pragma pack(push, 1)
enum  CommandType :  char
{
    PING = 'P',
    RUN = 'R',
    UNKOWN = '?',
};

typedef struct _PacketHeader {
    CommandType commandType;
    size_t dataSize;
} PacketHeader;
#pragma pack(pop)

class Packet {
  public:
    PacketHeader m_header;
    char* m_data;

    Packet(PacketHeader header, char* data);

    Packet(CommandType type, std::string data);
    
    Packet(char* packetData);

    ~Packet();

    Packet(const Packet& other);

    Packet& operator=(const Packet& other);

    std::vector<char> serialized();
};

void sendPacket(Socket sock, Packet packet);

Packet recvPacket(Socket sock);

void printPacket(Packet packet);
