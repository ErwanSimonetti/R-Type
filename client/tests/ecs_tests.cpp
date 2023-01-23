/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <gtest/gtest.h>
#include "registry.hpp"
#include "Components.hpp"

class registryTests: public ::testing::Test { 
public: 
   myTestFixture1( ) { 
       // initialization code here
   } 

   void SetUp( ) { 
       // code here will execute just before the test ensues 
   }

   void TearDown( ) { 
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
   }

   ~myTestFixture1( )  { 
       // cleanup any pending stuff, but no exceptions allowed
   }

   // put in any custom data members that you need 
};


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
    // EXPECT_EQ(reg.get_components<int>()[0].value(), firstTest);
    // EXPECT_EQ(reg.get_components<int>()[1].value(), secondTest);
    // EXPECT_EQ(reg.get_components<int>()[2].value(), thirdTest);
    // reg.get_components<int>().erase(1);
    // std::cout << reg.get_components<int>() << std::endl;
    // // std::cout << reg.get_components<int>()[1].value() << std::endl;
    // std::cout << reg.get_components<int>()[2].value() << std::endl;
    // std::cout << "OVER" << std::endl;
    // EXPECT_EQ(reg.get_components<int>()[0].value(), firstTest);
    // EXPECT_EQ(reg.get_components<int>()[2].value(), thirdTest);
    try
    {
        reg.get_components<Position>()[1].value();
    }
    catch(const std::exception& error) // this is expected because we're trying to see what's in an empty std::optional -> throws an error
    {
        // std::cout << error.what() << std::endl;
        EXPECT_EQ(error.what(), "bad optional acces");
    }
    
}
