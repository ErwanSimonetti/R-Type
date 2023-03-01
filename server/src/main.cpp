/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

#include <functional>
#include "Engine.hpp"

int main(void)
{   
    boost::asio::io_service io_service;
    Engine eng(1920, 1080, io_service, "1234");

    eng.run();
    return 0;
}
