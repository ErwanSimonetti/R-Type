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
#include "Engine_utils.hpp"

void collision_system(sparse_array<Position> &positions, sparse_array<Hitbox> &hitboxes);
void logging_system (sparse_array<Position> const& positions, sparse_array<Velocity> const& velocities);
void position_system(sparse_array<Position> &positions, const sparse_array<Velocity> &velocities);
void parallax_system(sparse_array<Animatable> &animatable, sparse_array<Position> &positions, sparse_array<Parallax> &parallax);
void animation_system(sparse_array<Animatable> &animatable, sparse_array<Drawable> &drawable);
EntityEvent control_system(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities);


#endif /* !SYSTEM_HPP_ */
