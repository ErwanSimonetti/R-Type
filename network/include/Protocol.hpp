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

/**
 * @brief manages the buffer and serializes data
 * 
 */
struct Header {
    uint16_t dataType;
    uint16_t dataSize;
};

/**
 * @brief holds information communicated between the client and the server
 * 
 */
struct ClientData {
    int16_t entity;
    int16_t directionsX;
    int16_t directionsY;
    bool shoot;
    uint16_t posX;
    uint16_t posY;
};

/**
 * @brief Holds information for the network
 * 
 */
struct ServerData {
    int16_t entities[4];
    uint16_t posX[4];
    uint16_t posY[4];
    int16_t directionsX[4];
    int16_t directionsY[4];
};

// enum DataTypes {
//     typeA = 1,
//     typeB = 2,
//     typeC = 3,
//     typeD = 4
// };

/**
 * @brief encapsulation of the protocol
 * 
 */
class Protocol {
    public:
        /**
         * @brief Construct a new Protocol object
         * 
         */
        Protocol();

        /**
         * @brief Destroy the Protocol object
         * 
         */
        ~Protocol();

        /**
         * @brief binarize data with his type
         * 
         * @tparam Data type of data
         * @param data struct of data
         * @return char* buffer
         */
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

        /**
         * @brief convert buffer to a data
         * 
         * @param buffer 
         * @return ClientData 
         */
        ClientData readClient(char *buffer) {
            // Header header;
            // std::memcpy(&header, buffer, sizeof(Header));
            ClientData clientData;
            std::memcpy(&clientData, buffer, sizeof(ClientData));
            return clientData;
        };

        /**
         * @brief convert buffer to data
         * 
         * @param buffer 
         * @return ServerData 
         */
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

void printClientData(const ClientData &data);
void printServerData(const ServerData &data);

#endif /* !PROTOCOL_HPP_ */
