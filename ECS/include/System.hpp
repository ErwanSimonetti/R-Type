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
#include "Drawable.hpp"
#include "Engine_utils.hpp"

/**
 * @brief system of logging displa all nodes with position and velocity
 * 
 * @param positions sparse array of positions
 * @param velocities sparse array of velocity
 */
void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);

/**
 * @brief follow path system, system for following path of IA
 * 
 * @param positions position array in ECS
 * @param velocities velocities array in ECS
 * @param paths paths array in ECS
 */
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities);

/**
 * @brief Control system, system emplacing the event corresponding to an interaction in the EntityEvent vector.
 * 
 * @param r  registery holding every entity
 * @param directions sparse array of directions
 * @param positions sparse array of positions
 * @param controllables sparse array of controllables
 * @param velocities sparse array of velocities
 * @return EntityEvent 
 */
EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities);

#endif /* !SYSTEM_HPP_ */
