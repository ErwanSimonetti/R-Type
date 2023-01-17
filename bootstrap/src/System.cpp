/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include "registry.hpp"
#include "components.hpp"

void logging_system(registry &r) {
    auto const &positions = r.get_components<position>() ;
    auto const &velocities = r.get_components<velocity>() ;
    for (size_t i = 0; i < positions.size() || i < velocities.size(); ++ i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos || vel)
            std::cerr << i;
        if (pos) {
            std::cerr << ": Position = { " << pos.value()._x << ", " << pos.value()._y << " } ";
        }
        if (vel) {
            std::cerr << ": Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }";
        }
        if (pos || vel)
            std::cerr << std::endl;
    }
}

void render_system(registry &r, sf::RenderWindow &window) {
    auto &drawables = r.get_components<drawable>();
    auto const &positions = r.get_components<position>();
    for (size_t i = 0; i < drawables.size(); ++ i) {
        // std::cout << "hello";
        window.clear();
        if (drawables[i]) {
        drawables[i].value()._sprite.setPosition(positions[i].value()._x, positions[i].value()._y);
        window.draw(drawables[i].value()._sprite);
        window.display();
        }
    }
}

void logging_system (sparse_array<position> const& positions,
    sparse_array<velocity> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions [i];
        auto const &vel = velocities [i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
            << " } , Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }" << std::endl;
        }
    }
}

void position_system(registry &r) {
    auto &positions = r.get_components<position>();
    auto const &velocities = r.get_components<velocity>();
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vx;
            pos.value()._y += vel.value()._vy;
        }
    }
}

void control_system(registry &r) {
}