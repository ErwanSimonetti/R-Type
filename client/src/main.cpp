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

    eng.create_parallax(1, 1920, 0, 3, PARA_1);
    eng.create_parallax(2, 0, 0, 3, PARA_1);
    eng.create_parallax(3, 1920, 0, 6, PARA_2);
    eng.create_parallax(4, 0, 0, 6, PARA_2);
    eng.create_parallax(5, 1920, 0, 9, PARA_3);
    eng.create_parallax(6, 0, 0, 9, PARA_3);
    eng.create_parallax(7, 1920, 346, 12, PARA_4);
    eng.create_parallax(8, 0, 346, 12, PARA_4);
    eng.create_player(9, 50, 50, 0, 0);
    eng.create_enemy_entity(10, -10, 1900, 200);

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