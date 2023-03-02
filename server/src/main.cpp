/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

// // #include "../include/RenderGame.hpp"
// #include "../include/components/Components.hpp"
// #include "../include/entity.hpp"
// #include "../include/registry.hpp"

#include <functional>
#include "Engine.hpp"

int main(int ac, char **av)
{   
    if (ac != 2) {
        std::cerr << "Need 2 arguments to launch" << std::endl;
        return 84;
    }
    boost::asio::io_service io_service;
    Engine eng(io_service, "172.17.0.1", "1234", av[1]);

    eng.run();
    return 0;
}
