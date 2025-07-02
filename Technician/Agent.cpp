#include "Agent.h"

#include <cstdio>
#include <iostream>
#include <vector>

Agent::Agent(): m_conn() , m_addr(NULL){
    //empty
}

void Agent::start() {

    try {
        initSocket();
        std::cout << "init socket\n";
        m_conn.bind(m_addr);
        std::cout << "bind socket\n";
        m_conn.listen();
        std::cout << "Listen....\n";
        handleClient();
    } catch (const AgentException& error) {
        std::cerr << "Error at: " << error.funcName << " Code: " << error.status << "\n ";
        closesocket(error.m_socket);
    
    } catch (const SocketException& error) {
        std::cerr << "Error at: " << error.funcName << " Code: " << error.status << "\n ";
        closesocket(error.m_socket);
    }
}

void Agent::initSocket() {
    m_addr = createAddress(DEFAULT_PORT);
    m_conn = Socket(m_addr);
}

void Agent::handleClient() {

    Socket clientConn = m_conn.accept();

    while (1) {
        auto recvbuf = clientConn.recv();
        std::cout << "Recv: " << recvbuf.data() << "\n";
        if (!strncmp(recvbuf.data(), REQUEST_STRING, recvbuf.size())) {
            agentSend(clientConn, RESPONSE_STRING);
            std::cout << "SEND: " << RESPONSE_STRING << "\n";
        }
    }
}
void Agent::agentSend(Socket sock, std::string message) {
    sock.send(const_cast<char*>(message.c_str()), message.size());
}


AgentException::AgentException(int status, std::string funcName, SOCKET sock)
    : Exception(status, funcName), m_socket(sock) {
    // i know this empty
}
