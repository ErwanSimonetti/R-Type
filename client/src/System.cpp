/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include "System.hpp"
#include "registry.hpp"
#include "SFML_utils.hpp"

void followPathSystem(const sparse_array<Position> &positions, sparse_array<Velocity> &velocities, const sparse_array<FollowPath> &paths) {
    int16_t xToReach = 0;
    int16_t yToReach = 0;
    int16_t newXVelocity = 0;
    int16_t newYVelocity = 0;

    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < paths.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &path = paths[i];

        if (pos && vel && path) {
            xToReach = path.value()._checkpoints[path.value()._current_checkpoint][0];
            yToReach = path.value()._checkpoints[path.value()._current_checkpoint][1];
            if (pos.value()._x < xToReach)
                newXVelocity = 1 * vel.value()._speedX;
            if (pos.value()._y < yToReach)
                newYVelocity = 1 * vel.value()._speedY;
            if (pos.value()._x > xToReach)
                newXVelocity = -1 * vel.value()._speedX;
            if (pos.value()._y > yToReach)
                newYVelocity = -1 * vel.value()._speedY;
            vel.value().build_component(newXVelocity, newYVelocity, vel.value()._speedX, vel.value()._speedY);
        }
    }
}

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
            << " } , Velocity = { " << vel.value()._vX << ", " << vel.value()._vY << " }" << std::endl;
        }
    }
}

void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vX;
            pos.value()._y += vel.value()._vY;
        }
    }
}

void control_system(registry &r, std::vector<int> &directions) {
    int current_direction = 0;
    int16_t xDirection = 0;
    int16_t yDirection = 0;
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
                        yDirection = -1; // FIXME: should be 1 and not minus
                        break;
                    case KEYBOARD::ARROW_LEFT:
                        xDirection = -1;
                        break;
                    case KEYBOARD::ARROW_RIGHT:
                        xDirection = 1;
                        break;
                    case KEYBOARD::ARROW_DOWN:
                        yDirection = 1;
                        break;
                    default:
                        xDirection = 0;
                        yDirection = 0;
                        break;
                }
            }
            if (directions.empty()) {
                xDirection = 0;
                yDirection = 0;
            }
            vel.value().build_component(xDirection * vel.value()._speedX, yDirection * vel.value()._speedY, vel.value()._speedX, vel.value()._speedY);
        }
    }
}