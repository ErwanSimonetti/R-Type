/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Protocol
*/

#include "Protocol.hpp"

Protocol::Protocol()
{
}

Protocol::~Protocol()
{
}

void printServerData(const ServerData &data) {
    std::cout << "entities: [";
    for (int i = 0; i < 4; i++) {
        std::cout << data.entities[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "posX: [";
    for (int i = 0; i < 4; i++) {
        std::cout << data.posX[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "posY: [";
    for (int i = 0; i < 4; i++) {
        std::cout << data.posY[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "directionsX: [";
    for (int i = 0; i < 4; i++) {
        std::cout << data.directionsX[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "directionsY: [";
    for (int i = 0; i < 4; i++) {
        std::cout << data.directionsY[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "hasShot: [";
    for (int i = 0; i < 4; i++) {
        std::cout << data.hasShot[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void printClientData(const ClientData &data) {
    std::cout << "entity: " << data.entity << std::endl;
    std::cout << "directionsX: " << data.directionsX << std::endl;
    std::cout << "directionsY: " << data.directionsY << std::endl;
    std::cout << "shoot: " << data.hasShot << std::endl;
    std::cout << "posX: " << data.posX << std::endl;
    std::cout << "posY: " << data.posY << std::endl;
}
