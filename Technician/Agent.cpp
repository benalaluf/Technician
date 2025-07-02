#include "Agent.h"

#include <cstdio>
#include <iostream>
#include <vector>

Agent::Agent() {
    m_conn = INVALID_SOCKET;
}

void Agent::start() {

    try {
        initSocket();
        std::cout << "init socket\n";
        bindSocket();
        std::cout << "bind socket\n";
        listenSocket();
        std::cout << "Listen....\n";
        handleClient();
    } catch (const AgentException& error) {
        std::cerr << "Error at: " << error.funcName << " Code: " << error.status << "\n ";
        closesocket(error.m_socket);
    }
}

void Agent::initSocket() {
    struct addrinfo *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &m_addr);
    if (result != 0) {
        throw AgentException(result, "initSocket getaddrinfo", m_conn);
    }

    m_conn = socket(m_addr->ai_family, m_addr->ai_socktype, m_addr->ai_protocol);

    if (m_conn == INVALID_SOCKET) {
        freeaddrinfo(m_addr);
        throw AgentException(WSAGetLastError(), "initSocket socket()", m_conn);
    }
}

void Agent::bindSocket() {
    int result = bind(m_conn, m_addr->ai_addr, (int)m_addr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        freeaddrinfo(m_addr);
        throw AgentException(WSAGetLastError(), "bindSocket bind()", m_conn);
    }
}

void Agent::listenSocket() {
    if (listen(m_conn, SOMAXCONN) == SOCKET_ERROR) {
        throw AgentException(WSAGetLastError(), "listen", m_conn);
    }
}

SOCKET Agent::agentAccept() {
    SOCKET ClientSocket = INVALID_SOCKET;
    ClientSocket = accept(m_conn, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        throw AgentException(WSAGetLastError(), "aggentAccept", m_conn);
    }
    return ClientSocket;
}

void Agent::handleClient() {

    SOCKET ClientSocket = agentAccept();

    while (1) {
        auto recvbuf = agentRecv(ClientSocket);
        std::cout << "Recv: " << recvbuf.data() << "\n";
        if (!strncmp(recvbuf.data(), REQUEST_STRING, recvbuf.size())) {
            agentSend(ClientSocket, RESPONSE_STRING);
            std::cout << "SEND: " << RESPONSE_STRING << "\n";
        }
    }
}
void Agent::agentSend(SOCKET sock, std::string message) {
    agentSend(sock, const_cast<char*>(message.c_str()), message.size());
}
void Agent::agentSend(SOCKET sock, char* data, size_t dataSize) {
    int iSendResult = send(sock, data, dataSize, 0);
    if (iSendResult == SOCKET_ERROR) {
        throw AgentException(WSAGetLastError(), "send", sock);
    }
}

std::vector<char> Agent::agentRecv(SOCKET sock) {
    std::vector<char> recvbuf(DEFAULT_BUFLEN);
    int recvResult;
    int recvbuflen = DEFAULT_BUFLEN;

    recvResult = recv(sock, recvbuf.data(), recvbuflen, 0);
    if (recvResult <= 0) {
        if (recvResult == 0) {
            throw AgentException(recvResult, "connection closed", sock);
        } else {
            throw AgentException(recvResult, "agent Recv", sock);
        }
    }

    return recvbuf;
}

AgentException::AgentException(int status, std::string funcName, SOCKET sock)
    : Exception(status, funcName), m_socket(sock) {
    // i know this empty
}
