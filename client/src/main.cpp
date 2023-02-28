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
    boost::asio::io_service io_service;
    Engine eng(io_service, "127.0.0.1", "1234", av[1]);

    eng.run();
    return 0;
}