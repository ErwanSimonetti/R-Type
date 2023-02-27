/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main2
*/

#include <functional>
#include "Engine.hpp"

void salut()
{
    std::cout << "hello";
}

int main(int ac, char **av)
{ 
    if (ac != 2) {
        return 84;
    }
    boost::asio::io_service io_service;
    Engine eng(io_service, "127.0.0.1", "1234", av[1]);
    printf("client\n");

    eng.run();
    return 0;
}