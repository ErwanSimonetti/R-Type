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
    uint16_t inputs[10];

struct ClientData
{
    int16_t entity;
    int16_t directionsX;
    int16_t directionsY;
    uint16_t hasShot;
    uint16_t posX;
    uint16_t posY;
};

struct ServerData
{
    int16_t entities[4];
    uint16_t posX[4];
    uint16_t posY[4];
    int16_t directionsX[4];
    int16_t directionsY[4];
    uint16_t hasShot[4];
};

struct ServerData {
    int16_t entities[4];
    uint16_t posX[4];
    uint16_t posY[4];
    uint16_t inputs[4][10];
};
struct ConnectionStatus
{
    bool isAccepted;
    int nbPlayer;
};


class Protocol {
    public:
        Protocol();
        ~Protocol();

        template <class Data>
        char *serialiseData(Data data) {
            char *buffer = new char[sizeof(Data)];
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
