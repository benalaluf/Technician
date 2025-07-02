#include "Socket.h"

#include <cstdio>
#include <iostream>
#include <vector>

Socket::Socket(): m_sock(INVALID_SOCKET) {
    // empty
}

Socket::Socket(struct addrinfo* addr) {
    m_sock = INVALID_SOCKET;
    m_sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    if (m_sock == INVALID_SOCKET) {
        throw SocketException(WSAGetLastError(), "Socket()", m_sock);
    }
}

Socket::Socket(SOCKET sock): m_sock(sock) {
    // empty
}

void Socket::bind(struct addrinfo* addr) {
    int result = ::bind(m_sock, addr->ai_addr, (int)addr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        throw SocketException(WSAGetLastError(), "bind()", m_sock);
    }
}

void Socket::connect() {
}

void Socket::listen() {
    if (::listen(m_sock, SOMAXCONN) == SOCKET_ERROR) {
        throw SocketException(WSAGetLastError(), "listen", m_sock);
    }
}

Socket Socket::accept() {
    SOCKET ClientSocket = INVALID_SOCKET;
    ClientSocket = ::accept(m_sock, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        throw SocketException(WSAGetLastError(), "accept()", m_sock);
    }
    return Socket(ClientSocket);
}

void Socket::send(char* data, size_t dataSize) {
    int iSendResult = ::send(m_sock, data, static_cast<int>(dataSize), 0);
    if (iSendResult == SOCKET_ERROR) {
        throw SocketException(WSAGetLastError(), "send", m_sock);
    }
}



std::vector<char> Socket::recv() {
    std::vector<char> recvbuf(DEFAULT_BUFLEN);
    int recvResult;
    int recvbuflen = DEFAULT_BUFLEN;

    recvResult = ::recv(m_sock, recvbuf.data(), recvbuflen, 0);
    if (recvResult <= 0) {
        if (recvResult == 0) {
            throw SocketException(recvResult, "connection closed", m_sock);
        } else {
            throw SocketException(recvResult, "recv()", m_sock);
        }
    }

    return recvbuf;
}

struct addrinfo* createAddress(std::string port) {
    struct addrinfo *ptr = NULL, *resultAddr = NULL, hints;
      
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int result = getaddrinfo(NULL, port.c_str(), &hints, &resultAddr);
    if (result != 0) {
        throw Exception(result, "createAddresss");
    }

    return resultAddr;
}

SocketException::SocketException(int status, std::string funcName, SOCKET sock): Exception(status, funcName), m_socket(sock) {
    //empty
}
