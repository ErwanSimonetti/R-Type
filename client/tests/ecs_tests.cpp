/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <gtest/gtest.h>
#include "registry.hpp"
#include "Position.hpp"


TEST(Step0, DefiningEntityAsSizeT) {
    entity a(0);
    entity b(42);
    size_t expected_a = 0;
    size_t expected_b = 42;

    EXPECT_EQ(a, expected_a);
    EXPECT_EQ(b, expected_b);
}

TEST(Step1, RegistryInsertAt) {
    registry reg;
    std::string firstTest = "Hello World !";
    std::string secondTest = "foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar foobar";
    std::string thirdTest = "";

    reg.register_component<std::string>();
    reg.get_components<std::string>().insert_at(0, firstTest);
    reg.get_components<std::string>().insert_at(1, secondTest);
    reg.get_components<std::string>().insert_at(42, thirdTest);
    EXPECT_EQ(reg.get_components<std::string>()[0].value(), firstTest);
    EXPECT_EQ(reg.get_components<std::string>()[1].value(), secondTest);
    EXPECT_EQ(reg.get_components<std::string>()[42].value(), thirdTest);
    try
    {
        EXPECT_EQ(reg.get_components<std::string>()[2].value(), "shouldn't go here");
    }
    catch(const std::exception& error) // this is expected because we're trying to see what's in an empty std::optional -> throws an error
    {
        EXPECT_EQ(error.what(), "bad optional access");
    }
}

TEST(Step1, RegistryErase) {
    registry reg;

    Position pos1;
    Position pos2;
    Position pos3;

    reg.register_component<Position>();
    reg.get_components<Position>().insert_at(0, Position());
    reg.get_components<Position>().insert_at(1, Position());
    reg.get_components<Position>().insert_at(2, Position());
    std::cout << "SPARSE ARRAY BEFORE ERASE : " << std::endl;
    std::cout << reg.get_components<Position>();
    int sizeBefore = reg.get_components<Position>().size();
    reg.get_components<Position>().erase(1);
    std::cout << "SPARSE ARRAY AFTER ERASE : " << std::endl;
    std::cout << reg.get_components<Position>();
    int sizeAfter = reg.get_components<Position>().size();
    EXPECT_EQ(sizeBefore, 3);
    EXPECT_EQ(sizeAfter, 2);
    try
    {
        reg.get_components<Position>()[1].value();
    }
    catch(const std::exception& error) // this is expected because we're trying to see what's in an empty std::optional -> throws an error
    {
        EXPECT_EQ(error.what(), "bad optional access");
    }
    
}
