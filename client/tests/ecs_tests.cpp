/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <gtest/gtest.h>
#include "registry.hpp"

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

    int firstTest = 0;
    int secondTest = -2147483647;
    int thirdTest = 42;

    reg.register_component<int>();
    reg.get_components<int>().insert_at(0, firstTest);
    reg.get_components<int>().insert_at(1, secondTest);
    reg.get_components<int>().insert_at(2, thirdTest);
    std::cout << "INT BEFORE ERASE : " << std::endl;
    std::cout << reg.get_components<int>()[0].value() << std::endl;
    std::cout << reg.get_components<int>()[1].value() << std::endl;
    std::cout << reg.get_components<int>()[2].value() << std::endl;
    std::cout << "OVER" << std::endl;
    EXPECT_EQ(reg.get_components<int>()[0].value(), firstTest);
    EXPECT_EQ(reg.get_components<int>()[1].value(), secondTest);
    EXPECT_EQ(reg.get_components<int>()[2].value(), thirdTest);
    reg.get_components<int>().erase(1);
    std::cout << "INT AFTER ERASE: " << std::endl;
    std::cout << reg.get_components<int>()[0].value() << std::endl;
    std::cout << reg.get_components<int>()[1].value() << std::endl;
    std::cout << reg.get_components<int>()[2].value() << std::endl;
    std::cout << "OVER" << std::endl;
    EXPECT_EQ(reg.get_components<int>()[0].value(), firstTest);
    EXPECT_EQ(reg.get_components<int>()[2].value(), thirdTest);
    try
    {
        EXPECT_EQ(reg.get_components<int>()[1].value(), -1);
    }
    catch(const std::exception& error) // this is expected because we're trying to see what's in an empty std::optional -> throws an error
    {
        EXPECT_EQ(error.what(), "bad optional acces");
    }
    
}
