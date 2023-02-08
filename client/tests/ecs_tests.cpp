/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <gtest/gtest.h>
#include "registry.hpp"
#include "Position.hpp"

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
