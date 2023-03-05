/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** system
*/

#include <cstdlib>

#include "System.hpp"
#include "registry.hpp"

void follow_path_system(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities, sparse_array<FollowPath> &paths) {
    int16_t xToReach = 0;
    int16_t yToReach = 0;
    int16_t newXVelocity = 0;
    int16_t newYVelocity = 0;

    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < paths.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &path = paths[i];

        if (pos && vel && path) {
            if (path.value()._currentCheckPoints > path.value()._checkpoints.size() - 1)
                return;
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

void position_system(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities, const sparse_array<Controllable> &controllables, sparse_array<Hitbox> &hitboxes) 
{
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos && vel) {
            if (i < hitboxes.size() && hitboxes[i]) {
                auto &hbx = hitboxes[i];

                if ((vel.value()._vX > 0 && hbx.value()._rightHit <= 0) || (vel.value()._vX < 0 && hbx.value()._leftHit <= 0))
                    pos.value()._x += vel.value()._vX;
                
                if ((vel.value()._vY < 0 && hbx.value()._bottomHit <= 0) || (vel.value()._vY > 0 && hbx.value()._topHit <= 0))
                    pos.value()._y += vel.value()._vY;
            } else {
                pos.value()._x += vel.value()._vX;
                pos.value()._y += vel.value()._vY;
            }

            if (i < controllables.size() && controllables[i]) {
                vel.value()._vX = 0;
                vel.value()._vY = 0;
            }
        }
    }
}

void shoot_system(registry &r, sparse_array<Shootable> &shootable) 
{
    for (size_t i = 0; i < shootable.size(); ++i) {
        auto &shoot = shootable[i];
        if (shoot) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - shoot.value()._clock);

            if (elapsedTime.count() >= 1000) {
                shoot.value()._canShoot = true;
            } else {
                shoot.value()._canShoot = false;
            }
        }
    }
}

bool isCollision(Position& a, Hitbox& aHitbox, Position& b, Hitbox& bHitbox)
{
   return (a._x < (b._x + bHitbox._width) && (a._x + aHitbox._width) > b._x && a._y < b._y + bHitbox._height && a._y + aHitbox._height > b._y);
}

void collision_system(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities,  sparse_array<Hitbox> &hitboxes)
{
    // reset all the _obstacles to re-assign them
    for (int i = 0; i < hitboxes.size(); ++i) {
        auto &hbx = hitboxes[i];
        if (!hbx)
            continue;
        hbx.value()._obstacle = -1;
        hbx.value()._topHit = -1;
        hbx.value()._bottomHit = -1;
        hbx.value()._leftHit = -1;
        hbx.value()._rightHit = -1;
    }

    for (int i = 0; i < positions.size() && i < velocities.size() && i < hitboxes.size(); ++i) {
        auto &hbxI = hitboxes[i];
        if (!hbxI)
            continue;
        for (int j = i + 1; j < positions.size() && j < hitboxes.size(); ++j) {
            auto &hbxJ = hitboxes[j];
            auto posI = positions[i];
            auto posJ = positions[j];
            if (!posI || !posJ || !hbxJ || !velocities[i] || !velocities[j])
                continue;

            if (isCollision(posI.value(), hbxI.value(), posJ.value(), hbxJ.value()) && hbxI.value()._active && hbxJ.value()._active) {
                hbxI.value()._obstacle = hbxJ.value()._type;
                hbxJ.value()._obstacle = hbxI.value()._type;
            }

            posI.value()._x += 1;
            if (isCollision(posI.value(), hbxI.value(), posJ.value(), hbxJ.value()) && hbxI.value()._active && hbxJ.value()._active) {
                hbxI.value()._leftHit = hbxJ.value()._type;
                hbxJ.value()._rightHit = hbxI.value()._type;
            }
            posI.value()._x -= 1;
            posI.value()._y += 1;
            if (isCollision(posI.value(), hbxI.value(), posJ.value(), hbxJ.value()) && hbxI.value()._active && hbxJ.value()._active) {
                hbxI.value()._topHit = hbxJ.value()._type;
                hbxJ.value()._bottomHit = hbxI.value()._type;
            }
            posI.value()._y -= 1;

            posJ.value()._x += 1;
            if (isCollision(posI.value(), hbxI.value(), posJ.value(), hbxJ.value()) && hbxI.value()._active && hbxJ.value()._active) {
                hbxI.value()._rightHit = hbxJ.value()._type;
                hbxJ.value()._leftHit = hbxI.value()._type;
            }
            posJ.value()._x -= 1;
            posJ.value()._y += 1;
            if (isCollision(posI.value(), hbxI.value(), posJ.value(), hbxJ.value()) && hbxI.value()._active && hbxJ.value()._active) {
                hbxI.value()._bottomHit = hbxJ.value()._type;
                hbxJ.value()._topHit = hbxI.value()._type;
            }
            posJ.value()._y -= 1;
        }
    }
}

void jump_system(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities, sparse_array<Hitbox> &hitboxes, sparse_array<Jump> &jumps, sparse_array<Gravity> &gravities)
{
    for (int i = 0; i < positions.size() && i < jumps.size() && i < gravities.size() && i < velocities.size() && i < hitboxes.size(); ++i) {
        auto &pos = positions[i];
        auto &jump = jumps[i];
        auto &gravity = gravities[i];
        auto &vel = velocities[i];
        auto &hitbox = hitboxes[i];
        if (!pos || !jump || !gravity || !vel || !hitbox) {
            continue;
        }

        if (jump.value()._stop == true) {
            jump.value()._canJump = true;
            jump.value()._isJumping = false;
            jump.value()._stop = false;
            jump.value()._hasReachedTheTop = false;
            continue;
        }

        if (jump.value()._canJump == true)
            continue;

        if (jump.value()._canJump == false && jump.value()._isJumping == false) {
            jump.value()._jumpHeight = pos.value()._y + jump.value()._jumpForce;
            vel.value()._vY = gravity.value()._force;
            vel.value()._speedY = 0;
            jump.value()._isJumping = true;
        }

        if (pos.value()._y >= jump.value()._jumpHeight) {
            vel.value().set_component(vel.value()._vX, -gravity.value()._force);
            jump.value()._hasReachedTheTop = true;
            jump.value()._stop = true;
        } else {
            if (hitbox.value()._topHit > 0 ) {
                jump.value()._stop = true;
                pos.value()._y -= 5;
            }
        }
        if (!jump.value()._hasReachedTheTop)
            vel.value().set_component(vel.value()._vX, gravity.value()._force * 2);
    }
}

void gravity_system(registry &r, sparse_array<Velocity> &velocities, sparse_array<Hitbox> &hitboxes, sparse_array<Gravity> &gravities)
{
    for (int i = 0; i < velocities.size() && i < hitboxes.size() && i < gravities.size(); ++i) {
        auto &vel = velocities[i];
        auto &hbx = hitboxes[i];
        auto &gravity = gravities[i];

        if (!vel || !hbx || !gravity)
            continue;

        if (hbx.value()._obstacle <= 0)
            vel.value()._vY = -gravity.value()._force;
    }
}

void entity_killing_system(registry &r, sparse_array<Stats> &stats, sparse_array<Position> &positions, sparse_array<Pet> &pets)
{
    for (int i = 0; i < stats.size() && i < positions.size() && i < pets.size(); ++i) {
        auto &sts = stats[i];
        auto &pos = positions[i];
        auto &pet = pets[i];
        if (sts && sts && sts.value()._health <= 0)
            r.kill_entity(entity(i));
        if (pet && pet.value()._ent == 0)
            r.kill_entity(entity(i));
    }
}

void update_drawable_texts_system(registry &r, sparse_array<Stats> &stats, sparse_array<DrawableText> &drawableTexts, sparse_array<Pet> &pets)
{
    for (int i = 0; i < drawableTexts.size() && i < pets.size(); ++i) {
        auto &pet = pets[i];
        auto &texts = drawableTexts[i];

        if (pet && texts) {
            if (pet.value()._ent < stats.size() && stats[pet.value()._ent]) {
                texts.value()._text = std::to_string(stats[pet.value()._ent].value()._score);
            }
        }
    }
}