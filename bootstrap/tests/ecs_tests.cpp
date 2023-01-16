/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <gtest/gtest.h>
#include "bootstrap.h"

TEST(Step0, DefiningEntityAsSizeT) {
  entity a(0);
  entity b(42);
  size_t expected_a = 0;
  size_t expected_b = 42;

  EXPECT_EQ(a, expected_a);
  EXPECT_EQ(b, expected_b);
}
