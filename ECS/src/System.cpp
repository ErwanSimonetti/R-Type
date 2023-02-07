/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

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

void position_system(sparse_array<Position> &positions, sparse_array<Velocity> &velocities) {
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vX;
            pos.value()._y += vel.value()._vY;
            vel.value()._vX = 0;
            vel.value()._vY = 0;
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

bool isCollision(Position& a, Hitbox& aHitbox, Position& b, Hitbox& bHitbox)
{
    return (a._x < b._x + bHitbox._width && a._x + aHitbox._width > b._x && a._y < b._y + bHitbox._height && a._y + aHitbox._height > b._y);
}

void collision_system(sparse_array<Position> &positions, sparse_array<Hitbox> &hitboxes)
{
    for (int i = 0; i < positions.size(); ++i) {
        for (int j = i + 1; j < positions.size(); ++j) {
            if (positions[i].has_value() && hitboxes[i].has_value() && positions[j].has_value() && hitboxes[j].has_value()) {
                if (isCollision(positions[i].value(), hitboxes[i].value(), positions[j].value(), hitboxes[j].value())) {
                    // std::cout << "jeanne au secours" << std::endl;
                }
            }
        }
    }
}
