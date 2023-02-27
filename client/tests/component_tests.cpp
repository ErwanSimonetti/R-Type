/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** component_tests
*/

#include <gtest/gtest.h>
#include "entity.hpp"
#include "registry.hpp"
#include "FollowPath.hpp"

TEST(FollowPath, checkingFileParsing) {
    registry testRegistry;
    entity testEntity(0);
    FollowPath testFollowPathComponent;

    testRegistry.register_component<FollowPath>();
    testRegistry.emplace_component<FollowPath>(testEntity, ".testing_file");
    testFollowPathComponent = testRegistry.get_components<FollowPath>()[testEntity].value();
    EXPECT_EQ(testFollowPathComponent._currentCheckPoints, 0);
    EXPECT_EQ(testFollowPathComponent._checkpoints[0][0], 1);
    EXPECT_EQ(testFollowPathComponent._checkpoints[0][1], 2);
    EXPECT_EQ(testFollowPathComponent._checkpoints[1][0], 21);
    EXPECT_EQ(testFollowPathComponent._checkpoints[1][1], 42);
    EXPECT_EQ(testFollowPathComponent._checkpoints[2][0], 12345);
    EXPECT_EQ(testFollowPathComponent._checkpoints[2][1], -9876);
}

TEST(FollowPath, checkingWrongFilePath) {
    registry testRegistry;
    entity testEntity(0);
    FollowPath testFollowPathComponent;

    testRegistry.register_component<FollowPath>();
    try
    {
        testRegistry.emplace_component<FollowPath>(testEntity, "foobar");
    }
    catch(const std::invalid_argument &error)
    {
        SUCCEED();
        return;
    }
    FAIL();
}