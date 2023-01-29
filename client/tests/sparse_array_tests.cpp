/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <gtest/gtest.h>
#include <optional>

#include "registry.hpp"
#include "Components.hpp"
#include "Position.hpp"
#include "sparse_array.hpp"

TEST(SparseArray, SizeAndInsertAt) {
    sparse_array<int> test;
    EXPECT_EQ(test.size(), 0);
    test.insert_at(0, 12);
    EXPECT_EQ(test.size(), 1);
}

TEST(SparseArray, EmptyAndInsertAt) {
    sparse_array<int> test;
    EXPECT_EQ(test.empty(), true);
    test.insert_at(0, 12);
    EXPECT_EQ(test.empty(), false);
}

TEST(SparseArray, OperatorPosForFullPos) {
    sparse_array<int> test;
    EXPECT_EQ(test.empty(), true);
    test.insert_at(0, 12);
    test.insert_at(1, 6);
    test.insert_at(4, 5);
    EXPECT_EQ(test[0], 12);
}

TEST(SparseArray, OperatorPosForNullPos) {
    sparse_array<int> test;
    EXPECT_EQ(test.empty(), true);
    test.insert_at(0, 12);
    test.insert_at(1, 6);
    test.insert_at(3, 5);
    EXPECT_EQ(test[3], 5);
    EXPECT_EQ(test[2], std::nullopt);
}

TEST(SparseArray, OperatorPosThrowExpectionOutOfRange) {
    sparse_array<int> test;
    try
    {
        std::cout << test[16].value() << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
        EXIT_SUCCESS;
    }
}
