cmake_minimum_required(VERSION 3.17)
project(r-type_client)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(USE_WAYLAND "ON")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SOURCE_FILES 
  src/main.cpp
  src/asio.cpp
  src/System.cpp
  src/Engine.cpp
  src/components/FollowPath.cpp
)

set(INCLUDE_DIRECTORY include/ include/components)

include_directories(${INCLUDE_DIRECTORY})
add_executable(r-type_client ${SOURCE_FILES})

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
    add_executable(r-type_client src/asio.cpp)
    target_link_libraries(r-type_client ${Boost_ASIO_LIBRARY} ${Boost_ARRAY_LIBRARY})
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

target_link_libraries(r-type_client PRIVATE sfml-graphics)
target_compile_features(r-type_client PRIVATE cxx_std_17)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS asio array) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(r-type_client src/asio.cpp)
    # target_link_libraries(progname ${Boost_LIBRARIES})
    target_link_libraries(r-type_client ${Boost_ASIO_LIBRARY} ${Boost_ARRAY_LIBRARY})
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings

enable_testing()

add_executable(
  clients_tests
  src/components/FollowPath.cpp
  tests/ecs_tests.cpp
  src/components/FollowPath.cpp
  tests/sparse_array_tests.cpp
  tests/entity_tests.cpp
  tests/registry_tests.cpp
  tests/component_tests.cpp
)
target_link_libraries(
  clients_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(clients_tests)