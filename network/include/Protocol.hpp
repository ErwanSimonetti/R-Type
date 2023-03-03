/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <iostream>
#include <cstring>

// struct Header {
//     uint16_t dataType;
//     uint16_t dataSize;
// };

struct ClientData {
    int16_t entity;
    uint16_t inputs[10];

};

struct ServerData {
    int16_t entities[4];
    uint16_t posX[4];
    uint16_t posY[4];
    uint16_t inputs[4][10];
};

class Protocol {
    public:
        Protocol();
        ~Protocol();

        template <class Data>
        char *serialiseData(Data data) {
            char *buffer = new char[sizeof(Data)];
            // Header header;

            // header.dataType = type;
            // header.dataSize = sizeof(Data);

            // std::memcpy(buffer, &header, sizeof(Header));
            std::memcpy(buffer, &data, sizeof(Data));

            return buffer;
        };

        ClientData readClient(char *buffer);
        ServerData readServer(char *buffer);

    protected:
    private:
};

void printClientData(const ClientData &data);
void printServerData(const ServerData &data);

#endif /* !PROTOCOL_HPP_ */
