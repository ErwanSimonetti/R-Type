/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include "System.hpp"
#include "registry.hpp"

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

EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities) {

    EntityEvent entityEvent;
    entityEvent.entity = -1;
    int current_direction = 0;
    int x_velocity = 0;
    int y_velocity = 0;
    for (size_t i = 0; i < velocities.size() && i < controllables.size() && i < positions.size(); ++ i) {
        auto &vel = velocities[i];
        auto &pos = positions[i];
        auto &contr = controllables[i];
        if (vel && contr && pos) {
            for(std::size_t j = 0; j < directions.size(); ++j) {
                entityEvent.entity = i;
                current_direction = directions[j];
                contr.value()._current_action = current_direction;
                switch (current_direction) {
                    case KEYBOARD::ARROW_UP:
                        y_velocity = -1; // FIXME: should be 1 and not minus
                        entityEvent.events.emplace_back(GAME_EVENT::UP);
                        break;
                    case KEYBOARD::ARROW_LEFT:
                        x_velocity = -1;
                        entityEvent.events.emplace_back(GAME_EVENT::LEFT);
                        break;
                    case KEYBOARD::ARROW_RIGHT:
                        x_velocity = 1;
                        entityEvent.events.emplace_back(GAME_EVENT::RIGHT);
                        break;
                    case KEYBOARD::ARROW_DOWN:
                        y_velocity = 1;
                        entityEvent.events.emplace_back(GAME_EVENT::RIGHT);
                        break;
                    case KEYBOARD::SPACE:
                        entityEvent.events.emplace_back(GAME_EVENT::SHOOT);
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
            vel.value().set_component(x_velocity, y_velocity);
        }
    }
    return entityEvent;
}