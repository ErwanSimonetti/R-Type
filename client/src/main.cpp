/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main2
*/

#include <functional>
#include "Engine.hpp"

int main(void)
{   
    boost::asio::io_service io_service;
    Engine eng(1920, 1080, io_service, "127.0.0.1", "1234");
    printf("client\n");

    eng.create_player(1, sf::Color::Blue, 50, 50, 0, 0);
    eng.run();
    // ClientData clientData;
    // clientData.event = 12;
    // strcpy(clientData.string, "you massive fuck");

    // Protocol prot;
    // // DataTypes lel = typeA;
    // char *ok = prot.serialiseData<ClientData>(clientData);
    // // ClientData test;
    // // std::memcpy(&test, ok, sizeof(ClientData));
    // // std::cerr << test.event << " " << test.string << "\n\n";
    // eng._network.udpSend<ClientData>(ok, eng._network._endpoints.at(0));
    // eng.printMonCul();

    return 0;
}