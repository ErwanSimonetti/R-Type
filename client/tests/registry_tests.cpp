/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** registry_tests
*/

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

#include "registry.hpp"
#include "entity.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

TEST(Registry, RegisterComponent) {
    registry res;
    res.register_component<Position>();
    res.register_component<Velocity>();

    entity a = res.spawn_entity();
    Position pos;
    Velocity vel;
    pos.build_component(1, 1);
    vel.build_component(3, 4, 5, 6);


    res.add_component(a, std::move(pos));
    res.add_component(a, std::move(vel));
    EXPECT_EQ(res.get_components<Position>().size(), 1);
    EXPECT_EQ(res.get_components<Velocity>().size(), 1);
    EXPECT_EQ(res.get_components<Position>()[0].value()._x, 1);
    EXPECT_EQ(res.get_components<Position>()[0].value()._y, 1);
}
