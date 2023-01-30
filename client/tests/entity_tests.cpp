/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** entity_tests
*/

#include <gtest/gtest.h>

#include "entity.hpp"

TEST(Entity, ConvertToSizeT) {
    entity a(0);
    entity b(42);
    size_t expected_a = 0;
    size_t expected_b = 42;

    EXPECT_EQ(a, expected_a);
    EXPECT_EQ(b, expected_b);
}
