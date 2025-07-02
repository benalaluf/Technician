#include "Protocol.h"

#include <memory>
#include <iostream>

Packet::Packet(PacketHeader header, char* data) : m_header(header) {
    m_data = new char;
    memcpy(m_data, data, header.dataSize);
}

Packet::Packet(CommandType type, std::string data) {
    m_header.commandType = type;
    m_header.dataSize = data.size() + 1;

    m_data = new char[m_header.dataSize];
    memcpy(m_data, data.c_str(), m_header.dataSize);
}

Packet::Packet(char* packetData) {
    memcpy(&m_header, packetData, sizeof PacketHeader);

    m_data = new char[m_header.dataSize];
    memcpy(m_data, packetData+ sizeof PacketHeader, m_header.dataSize);
}

Packet::~Packet() {
    delete[] m_data;
}

Packet::Packet(const Packet& other): m_header(other.m_header){
    m_data = new char[m_header.dataSize];
    memcpy(m_data, other.m_data, m_header.dataSize);
}
Packet& Packet::operator=(const Packet& other){
    m_header = other.m_header;

    m_data = new char[m_header.dataSize];
    memcpy(m_data, other.m_data, m_header.dataSize);

    return *this;
};


std::vector<char> Packet::serialized() {
    std::vector<char> buffer(MAX_PACKET_SIZE);

    memcpy(buffer.data(), &m_header, sizeof PacketHeader);
    memcpy(buffer.data() + sizeof PacketHeader, m_data, m_header.dataSize);

    return buffer;
}

void sendPacket(Socket sock, Packet packet) {
    sock.send(packet.serialized().data(), sizeof PacketHeader + packet.m_header.dataSize);
}

Packet recvPacket(Socket sock) {
    std::vector<char> headerBuffer = sock.recv(sizeof PacketHeader);
    PacketHeader* header = reinterpret_cast<PacketHeader*>(headerBuffer.data());

    if (header->dataSize) {
        std::vector<char> dataBuffer = sock.recv(header->dataSize);
        headerBuffer.insert(headerBuffer.end(), dataBuffer.begin(), dataBuffer.end());
    }

    return Packet(headerBuffer.data());
}

void printPacket(Packet packet)  {
    std::cout << "Type: " << static_cast<char>(packet.m_header.commandType) << "\n";
    std::cout << "size: " << packet.m_header.dataSize << "\n";
    std::cout << "data: " << packet.m_data << "\n";
}
