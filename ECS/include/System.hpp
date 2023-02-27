/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System
*/

// #pragma once

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "sparse_array.hpp"
#include "registry.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Controllable.hpp"
#include "Pet.hpp"
#include "Hitbox.hpp"
#include "Drawable.hpp"
#include "Animatable.hpp"
#include "Parallax.hpp"
#include "FollowPath.hpp"
#include "Shootable.hpp"
#include "GameEvents.hpp"

/**
 * @brief logging system displaying all nodes with their position & velocity
 * 
 * @param r registry modifiable object for change data in the ECS
 * @param positions sparse array of positions
 * @param velocities sparse array of velocity
 */
void logging_system (registry &r, sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);

/**
 * @brief position system, used to manage position of entities according to their velocity.
 * 
 * @param r registry modifiable object for change data in the ECS
 * @param positions position array in ECS
 * @param velocities velocities array in ECS
 * @param controllable controllable array in ECS
 */
void position_system(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities, const sparse_array<Controllable> &controllables);

/**
 * @brief Control system, system emplacing the event corresponding to an interaction in the EntityEvent vector.
 * 
 * @param r  registery holding every entity
 * @param directions sparse array of directions
 * @param positions sparse array of positions
 * @param controllables sparse array of controllables
 * @param velocities sparse array of velocities
 * @param shootable sparse array of shootable
 * @return EntityEvent 
 */
EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities, sparse_array<Shootable> &shootable);

/**
 * @brief System used to move enemies according to a specific path
 * 
 * @param positions sparseArray containing entity positions
 * @param velocities sparseArray containing entity velocities
 * @param paths paths to follow
 */

void collision_system(registry &r, sparse_array<Position> &positions, sparse_array<Hitbox> &hitboxes);
void parallax_system(registry &r, sparse_array<Animatable> &animatable, sparse_array<Position> &positions, sparse_array<Parallax> &parallax);
void animation_system(registry &r, sparse_array<Animatable> &animatable, sparse_array<Drawable> &drawable);
void shoot_system(registry &r, sparse_array<Shootable> &shootable);

#endif /* !SYSTEM_HPP_ */
