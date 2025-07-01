#include "Agent.h"

#include <cstdio>
#include <iostream>

Agent::Agent() {
}

void Agent::start() {
    initSocket();
    std::cout << "init socket\n";
    bindSocket();
    std::cout << "bind socket\n";
    listenSocket();
    std::cout << "Listen....\n";
    handleClient();
}

void Agent::initSocket() {
    struct addrinfo *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    auto iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &m_addr);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        // return 1;
    }

    m_conn = INVALID_SOCKET;
    // Create a SOCKET for the server to listen for client connections

    m_conn = socket(m_addr->ai_family, m_addr->ai_socktype, m_addr->ai_protocol);

    if (m_conn == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(m_addr);
        WSACleanup();
        // return 1;
    }
}

void Agent::bindSocket() {
    auto iResult = bind(m_conn, m_addr->ai_addr, (int)m_addr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(m_addr);
        closesocket(m_conn);
        WSACleanup();
        // return 1;
    }
}

void Agent::listenSocket() {
    if (listen(m_conn, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        closesocket(m_conn);
        WSACleanup();
        // return 1;
    }
}

void Agent::handleClient() {
    SOCKET ClientSocket = INVALID_SOCKET;

    // Accept a client socket
    ClientSocket = accept(m_conn, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(m_conn);
        WSACleanup();
        //return 1;
    }

    #define DEFAULT_BUFLEN 512

    char recvbuf[DEFAULT_BUFLEN];
    int iResult, iSendResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                //return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        } else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            //return 1;
        }

    } while (iResult > 0);
}
