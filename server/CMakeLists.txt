cmake_minimum_required(VERSION 3.17)
project(r-type_server)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(USE_WAYLAND "ON")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SOURCE_FILES 
  src/main.cpp
  src/Engine.cpp
  ../ECS/src/System.cpp
  ../network/src/MyNetwork.cpp
  ../network/src/Protocol.cpp
)

set(INCLUDE_DIRECTORY include/ include/utils ../network/include ../ECS/include/components ../ECS/include)

include_directories(${INCLUDE_DIRECTORY})
add_executable(r-type_server ${SOURCE_FILES})

if(DEFINED TEST_ENABLE AND "${TEST_ENABLE}" STREQUAL "yes")
    message(STATUS "Unit testing enabled")
    add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS system asio array) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(r-type_server src/asio.cpp)
    target_link_libraries(r-type_server ${Boost_ASIO_LIBRARY} ${Boost_ARRAY_LIBRARY})
endif()

set(CMAKE_CXX_STANDARD 17)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x  
)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)


FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(googletest)

target_link_libraries(r-type_server PRIVATE sfml-graphics)
target_compile_features(r-type_server PRIVATE cxx_std_17)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_server> $<TARGET_FILE_DIR:r-type_server> COMMAND_EXPAND_LISTS)
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS asio array) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(r-type_server src/asio.cpp)
    # target_link_libraries(progname ${Boost_LIBRARIES})
    target_link_libraries(r-type_server ${Boost_ASIO_LIBRARY} ${Boost_ARRAY_LIBRARY})
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings

enable_testing()

add_executable(
  ecs_tests
  tests/sample_test.cpp
)
target_link_libraries(
  ecs_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ecs_tests)