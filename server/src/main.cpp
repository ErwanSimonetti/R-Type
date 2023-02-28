/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

#include <functional>
#include "Engine.hpp"

int main(int ac, char **av)
{   
    boost::asio::io_service io_service;
    std::cout << "creating engine" << std::endl;
    Engine eng(io_service, "127.0.0.1", "1234", av[1]);

    std::cout << "running engine" << std::endl;
    eng.run();
    return 0;
}
