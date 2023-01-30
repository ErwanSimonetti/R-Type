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

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities);
std::pair<uint16_t, uint16_t> control_system(registry &r, std::vector<int> &directions);


#endif /* !SYSTEM_HPP_ */
