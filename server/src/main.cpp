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

void salut()
{
    std::cout << "hello";
}

int main(void)
{   
    boost::asio::io_service io_service;
    Engine eng(1920, 1080, io_service, "1234");
    printf("server\n");

    eng.run();
    return 0;
}
