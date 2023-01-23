/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include "System.hpp"
#include "registry.hpp"
#include "SFML_utils.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
            << " } , Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }" << std::endl;
        }
    }
}

void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vx;
            pos.value()._y += vel.value()._vy;
        }
    }
}

void control_system(registry &r, const int &direction) {
    auto &velocities = r.get_components<Velocity>();
    auto &controllables = r.get_components<Controllable>();
    auto &positions = r.get_components<Position>();
    for (size_t i = 0; i < velocities.size() && i < controllables.size() && i < positions.size(); ++ i) {
        auto &vel = velocities[i];
        auto &contr = controllables[i];
        if (vel && contr) {
            contr.value()._current_action = direction;
            switch (direction) {
            case KEYBOARD::ARROW_UP:
                vel.value().build_component(0, -1);
                break;
            case KEYBOARD::ARROW_LEFT:
                vel.value().build_component(-1, 0);
                break;
            case KEYBOARD::ARROW_RIGHT:
                vel.value().build_component(1, 0);
                break;
            case KEYBOARD::ARROW_DOWN:
                vel.value().build_component(0, 1);
                break;
            case KEYBOARD::NONE:
                vel.value().build_component(0, 0);
                break;
            }
        }
    }
    for (size_t i = 0; i < velocities.size() && i < positions.size(); ++ i) {
        auto &vel = velocities[i];
        auto &contr = controllables[i];
        auto &pos = positions[i];
        if (vel && !contr && pos.value()._x <= 1900) {
            vel.value().build_component(1, 0);
        }
    }
}