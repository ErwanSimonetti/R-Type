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
#include "FollowPath.hpp"

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities);
EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities);
void followPathSystem(const sparse_array<Position> &positions, sparse_array<Velocity> &velocities, sparse_array<FollowPath> &paths);


#endif /* !SYSTEM_HPP_ */
