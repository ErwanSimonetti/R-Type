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
    Engine eng(1920, 1080);

    eng.create_friendly_entity(1, sf::Color::Blue, 10, 20, 0, 0);
    eng.create_enemy_entity(2, sf::Color::Red, 7, 14, 2000, 2000);
    eng.run_game();
    return 0;
}
