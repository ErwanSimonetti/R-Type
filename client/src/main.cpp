/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main2
*/

#include <functional>
#include "Engine.hpp"

int main(int ac, char **av)
{   
    if (ac != 3) {
        return 0;
    }
    boost::asio::io_service io_service;
    Engine eng(io_service, "172.17.0.1", "1234", av[1], av[2]);

    eng.run();
    return 0;
}