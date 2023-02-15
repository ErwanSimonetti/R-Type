/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include <cstdlib>

#include "System.hpp"
#include "registry.hpp"

void followPathSystem(registry &r, const sparse_array<Position> &positions, sparse_array<Velocity> &velocities, sparse_array<FollowPath> &paths) {
    int16_t xToReach = 0;
    int16_t yToReach = 0;
    int16_t newXVelocity = 0;
    int16_t newYVelocity = 0;

    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < paths.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &path = paths[i];

        if (pos && vel && path) {
            xToReach = path.value()._checkpoints[path.value()._currentCheckPoints][0];
            yToReach = path.value()._checkpoints[path.value()._currentCheckPoints][1];
            if (pos.value()._x < xToReach)
                newXVelocity = 1 * vel.value()._speedX;
            if (pos.value()._x > xToReach)
                newXVelocity = -1 * vel.value()._speedX;
            if (pos.value()._y < yToReach)
                newYVelocity = 1 * vel.value()._speedY;
            if (pos.value()._y > yToReach)
                newYVelocity = -1 * vel.value()._speedY;
            if (std::abs(pos.value()._x - xToReach) <= 10 && std::abs(pos.value()._y - yToReach) <= 10)
                path.value()._currentCheckPoints += 1;
            vel.value().set_component(newXVelocity, newYVelocity);
        }
    }
}

void parallax_system(registry &r, sparse_array<Animatable> &animatable, sparse_array<Position> &positions, sparse_array<Parallax> &parallax) {
    for (size_t i = 0; i < positions.size() && i < animatable.size() && i < parallax.size(); ++ i) {
        auto &pos = positions[i];
        auto &anim = animatable[i];
        auto &para = parallax[i];
        if(pos && anim && para) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - anim.value()._clock);
            if (elapsedTime.count() >= 10) {
                pos.value()._x -= anim.value()._speed;
                anim.value()._clock = currentTime;
            }
            if (pos.value()._x <= para.value()._endPos) {
                pos.value()._x = para.value()._startPos;
            }
        }
    }
}

void logging_system(registry &r, sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
            << " } , Velocity = { " << vel.value()._vX << ", " << vel.value()._vY << " }" << std::endl;
        }
    }
}

void position_system(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities, const sparse_array<Controllable> &controllables) 
{
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (vel && (vel.value()._vX != 0 || vel.value()._vY != 0)) {
            std::cout << "vel x = " << vel.value()._vX << std::endl;
            std::cout << "vel y = " << vel.value()._vY << std::endl;
        }
        std::cout << "pos x = " << pos.value()._x << std::endl;
        std::cout << "pos y = " << pos.value()._y << std::endl;
        if (pos && vel) {
            pos.value()._x += vel.value()._vX;
            pos.value()._y += vel.value()._vY;
        }
    }
}

void shoot_system(registry &r, sparse_array<Shootable> &shootable) 
{
    for (size_t i = 0; i < shootable.size(); ++i) {
        auto &shoot = shootable[i];
        if (shoot) {
            if (shoot.value()._clock.getElapsedTime().asMilliseconds() <= 1000) {
                shoot.value()._canShoot = false;
            } else {
                shoot.value()._canShoot = true;
            }
        }
    }
}

EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities, sparse_array<Shootable> &shootable) {

    EntityEvent entityEvent;
    int current_direction = 0;

    entityEvent.entity = -1;
    entityEvent.xVelocity = 0;
    entityEvent.yVelocity = 0;
    for (size_t i = 0; i < velocities.size() && i < controllables.size() && i < positions.size() && i < shootable.size(); ++ i) {
        auto &vel = velocities[i];
        auto &pos = positions[i];
        auto &contr = controllables[i];
        auto &shoot = shootable[i];
        if (vel && contr && pos && shoot) {
            for(std::size_t j = 0; j < directions.size(); ++j) {
                entityEvent.entity = i;
                current_direction = directions[j];
                contr.value()._current_action = current_direction;
                switch (current_direction) {
                    case KEYBOARD::ARROW_UP:
                        entityEvent.yVelocity = -1 * vel.value()._speedY;
                        break;
                    case KEYBOARD::ARROW_DOWN:
                        entityEvent.yVelocity = vel.value()._speedY;
                        break;
                    case KEYBOARD::ARROW_LEFT:
                        entityEvent.xVelocity = -1 * vel.value()._speedX;
                        break;
                    case KEYBOARD::ARROW_RIGHT:
                        entityEvent.xVelocity = vel.value()._speedX;
                        break;
                    case KEYBOARD::SPACE:
                        if (shoot.value()._canShoot == true) {
                            entityEvent.events.emplace_back(GAME_EVENT::SHOOT);
                            shoot.value()._clock.restart();
                        }
                        break;
                    default:
                        entityEvent.xVelocity = 0;
                        entityEvent.yVelocity = 0;
                        break;
                }
            }
            if (directions.empty()) {
                entityEvent.xVelocity = 0;
                entityEvent.yVelocity = 0;
            }
        }
    }
    return entityEvent;
}

bool isCollision(Position& a, Hitbox& aHitbox, Position& b, Hitbox& bHitbox)
{
   return (a._x < b._x + bHitbox._width && a._x + aHitbox._width > b._x && a._y < b._y + bHitbox._height && a._y + aHitbox._height > b._y);
}

void collision_system(registry &r, sparse_array<Position> &positions, sparse_array<Hitbox> &hitboxes)
{
    for (int i = 0; i < positions.size() && i < hitboxes.size(); ++i) {;
        for (int j = i + 1; j < positions.size() && j < hitboxes.size(); ++j) {
            auto &hbxI = hitboxes[i];
            auto &hbxJ = hitboxes[j];
            if (positions[i] && hbxI && positions[j] && hbxJ 
                && isCollision(positions[i].value(), hbxI.value(), positions[j].value(), hbxJ.value())) {
                    if ((hbxI.value()._type == ENEMYSHIP || hbxI.value()._type == BULLET)
                     && (hbxJ.value()._type == ENEMYSHIP || hbxJ.value()._type == BULLET) 
                     && hbxI.value()._active && hbxJ.value()._active ) {
                        hbxI.value()._active = false;
                        hbxJ.value()._active = false;
                        r.kill_entity(entity(i));
                        r.kill_entity(entity(j));
                }
            }
        }
    }
}
