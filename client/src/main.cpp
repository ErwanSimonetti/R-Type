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
#include "../include/Engine.hpp"

int main(void)
{   
    Engine eng(1920, 1080);

    eng.create_friendly_entity(sf::Color::Blue, 50, 50, 0, 0);
    eng.create_enemy_entity(sf::Color::Red, 50, 50, 150, 150);
    // eng.create_projectile(sf::Color::Green, )
    eng.run_game();
    return 0;
}
