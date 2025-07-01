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
    }
    catch (const AgentException& error) {
        std::cerr << "Error at: " << error.funcName << "\n";
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
        printf("getaddrinfo failed: %d\n", result);
        throw AgentException(1, "initSocket getaddrinfo");
    }

    m_conn = socket(m_addr->ai_family, m_addr->ai_socktype, m_addr->ai_protocol);

    if (m_conn == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(m_addr);
        throw AgentException(1, "initSocket socket()");
    }
}

void Agent::bindSocket() {
    int result = bind(m_conn, m_addr->ai_addr, (int)m_addr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(m_addr);
        closesocket(m_conn);
        throw AgentException(1, "bindSocket bind()");
    }
}

void Agent::listenSocket() {
    if (listen(m_conn, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        closesocket(m_conn);
        throw AgentException(1, "listen");
    }
}

SOCKET Agent::agentAccept() {
    SOCKET ClientSocket = INVALID_SOCKET;
    ClientSocket = accept(m_conn, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(m_conn);
        throw AgentException(1, "aggentAccept");
    }
    return ClientSocket;
}

void Agent::handleClient() {

    SOCKET ClientSocket = agentAccept();

    while (1) {
        auto recvbuf = agentRecv(ClientSocket);
   
		if (!strncmp(recvbuf.data(), "PING", recvbuf.size())) {
            agentSend(ClientSocket, NULL);
		}
    }

}
void Agent::agentSend(SOCKET sock, char*  data) {
    int iSendResult = send(sock, "PONG",5, 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(sock);
        throw AgentException(1, "send");
    }
    printf("Bytes sent: %d\n", iSendResult);
}

std::vector<char> Agent::agentRecv(SOCKET sock) {
    std::vector<char> recvbuf(DEFAULT_BUFLEN);
    int recvResult;
    int recvbuflen = DEFAULT_BUFLEN;

    recvResult = recv(sock, recvbuf.data(), recvbuflen, 0);
    std::cout << recvbuf.data();
    if (recvResult <= 0) {
        if (recvResult == 0) {
            throw AgentException(recvResult, "connection closed");
        }  else {
            throw AgentException(recvResult, "agent Recv");
        }
    }

    return recvbuf;
}

AgentException::AgentException(int status, std::string funcName) : Exception(status, funcName) {
    // i know this empty
}
