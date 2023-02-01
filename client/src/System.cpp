/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include "System.hpp"
#include "registry.hpp"
#include "SFML_utils.hpp"

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
            << " } , Velocity = { " << vel.value()._v_x << ", " << vel.value()._v_y << " }" << std::endl;
        }
    }
}

void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._v_x * vel.value()._speed_x;
            pos.value()._y += vel.value()._v_y * vel.value()._speed_y;
        }
    }
}

void control_system(registry &r, std::vector<int> &directions) {
    int current_direction = 0;
    uint16_t x_velocity = 0;
    uint16_t y_velocity = 0;
    auto &velocities = r.get_components<Velocity>();
    auto &controllables = r.get_components<Controllable>();
    auto &positions = r.get_components<Position>();
    for (size_t i = 0; i < velocities.size() && i < controllables.size() && i < positions.size(); ++ i) {
        auto &vel = velocities[i];
        auto &contr = controllables[i];
        if (vel && contr) {
            for(std::size_t i = 0; i < directions.size(); ++i) {
                current_direction = directions[i];
                contr.value()._current_action = current_direction;
                switch (current_direction) {
                    case KEYBOARD::ARROW_UP:
                        y_velocity = -1; // FIXME: should be 1 and not minus
                        break;
                    case KEYBOARD::ARROW_LEFT:
                        x_velocity = -1;
                        break;
                    case KEYBOARD::ARROW_RIGHT:
                        x_velocity = 1;
                        break;
                    case KEYBOARD::ARROW_DOWN:
                        y_velocity = 1;
                        break;
                    default:
                        x_velocity = 0;
                        y_velocity = 0;
                        break;
                }
            }
            if (directions.empty()) {
                x_velocity = 0;
                y_velocity = 0;
            }
            vel.value().build_component(x_velocity, y_velocity, vel.value()._speed_x, vel.value()._speed_y);
        }
    }
}