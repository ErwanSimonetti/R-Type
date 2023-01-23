/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** system
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "sparse_array.hpp"
#include "Components.hpp"
#include "registry.hpp"

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities);
void control_system(registry &r, const int &direction);


#endif /* !SYSTEM_HPP_ */
