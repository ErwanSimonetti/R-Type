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

struct Header {
    uint16_t dataType;
    uint16_t dataSize;
};

struct ClientData {
    int16_t entity;
    int16_t directionsX;
    int16_t directionsY;
    bool shoot;
    uint16_t posX;
    uint16_t posY;
};

struct ServerData {
    uint16_t entity[4];
    uint16_t posX[4];
    uint16_t posY[4];
};

// enum DataTypes {
//     typeA = 1,
//     typeB = 2,
//     typeC = 3,
//     typeD = 4
// };

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

        ClientData readClient(char *buffer) {
            // Header header;
            // std::memcpy(&header, buffer, sizeof(Header));
            ClientData clientData;
            std::memcpy(&clientData, buffer, sizeof(ClientData));
            return clientData;
        };

        ServerData readServer(char *buffer) {
            // Header header;
            // std::memcpy(&header, buffer, sizeof(Header));
            ServerData serverData;
            std::memcpy(&serverData, buffer, sizeof(ServerData));
            return serverData;
        };

    protected:
    private:
};

<<<<<<< HEAD
void printClientData(const ClientData &data);
void printServerData(const ServerData &data);

=======
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
#endif /* !PROTOCOL_HPP_ */
