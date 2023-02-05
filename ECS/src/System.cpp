/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

<<<<<<< HEAD
#include <cstdlib>
#include "System.hpp"
#include "registry.hpp"

void followPathSystem(const sparse_array<Position> &positions, sparse_array<Velocity> &velocities, sparse_array<FollowPath> &paths) {
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
            if (std::abs(pos.value()._x - xToReach) <= 10 && std::abs(pos.value()._y - yToReach) <= 10)
                path.value()._current_checkpoint += 1;
            vel.value().set_component(newXVelocity, newYVelocity, vel.value()._speedX, vel.value()._speedY);
        }
    }
}

=======
#include "System.hpp"
#include "registry.hpp"

>>>>>>> b364e23 (feat: Refactored everything)
void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
<<<<<<< HEAD
            << " } , Velocity = { " << vel.value()._vX << ", " << vel.value()._vY << " }" << std::endl;
=======
            << " } , Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }" << std::endl;
>>>>>>> b364e23 (feat: Refactored everything)
        }
    }
}

<<<<<<< HEAD
void position_system(sparse_array<Position> &positions, sparse_array<Velocity> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vX;
            pos.value()._y += vel.value()._vY;
            vel.value()._vX = 0;
            vel.value()._vY = 0;
=======
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vx;
            pos.value()._y += vel.value()._vy;
>>>>>>> b364e23 (feat: Refactored everything)
        }
    }
}

EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities) {

    EntityEvent entityEvent;
    entityEvent.entity = -1;
    int current_direction = 0;
<<<<<<< HEAD
    int16_t xDirection = 0;
    int16_t yDirection = 0;
=======
    int x_velocity = 0;
    int y_velocity = 0;
>>>>>>> b364e23 (feat: Refactored everything)
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
<<<<<<< HEAD
                        yDirection = -1; // FIXME: should be 1 and not minus
                        entityEvent.events.emplace_back(GAME_EVENT::UP);
                        break;
                    case KEYBOARD::ARROW_DOWN:
                        yDirection = 1;
                        entityEvent.events.emplace_back(GAME_EVENT::DOWN);
                        break;
                    case KEYBOARD::ARROW_LEFT:
                        xDirection = -1;
                        entityEvent.events.emplace_back(GAME_EVENT::LEFT);
                        break;
                    case KEYBOARD::ARROW_RIGHT:
                        xDirection = 1;
                        entityEvent.events.emplace_back(GAME_EVENT::RIGHT);
                        break;
                    default:
                        xDirection = 0;
                        yDirection = 0;
=======
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
                    default:
                        x_velocity = 0;
                        y_velocity = 0;
>>>>>>> b364e23 (feat: Refactored everything)
                        break;
                }
            }
            if (directions.empty()) {
<<<<<<< HEAD
                xDirection = 0;
                yDirection = 0;
            }
            vel.value().set_component(xDirection * vel.value()._speedX, yDirection * vel.value()._speedY, vel.value()._speedX, vel.value()._speedY);
        }
    }
=======
                x_velocity = 0;
                y_velocity = 0;
            }
            vel.value().set_component(x_velocity, y_velocity);
        }
    }
    // for (size_t i = 0; i < velocities.size() && i < positions.size(); ++ i) {
    //     auto &vel = velocities[i];
    //     auto &contr = controllables[i];
    //     auto &pos = positions[i];
    //     if (vel && !contr && pos.value()._x <= 1900) {
    //         vel.value().set_component(1, 0);
    //     }
    // }
>>>>>>> b364e23 (feat: Refactored everything)
    return entityEvent;
}