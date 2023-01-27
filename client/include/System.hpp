/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System
*/

#pragma once

#include "components/Components.hpp"
#include "../include/registry.hpp"

void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);
void control_system(registry &r, const int &direction);
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities);
