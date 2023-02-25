cmake_minimum_required(VERSION 3.17)
project(r-type-modules)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(USE_WAYLAND "ON")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SFML_SOURCE_FILES
    graphics/SFML/src/SFML.cpp
)

set(RTYPE_SOURCE_FILES
    games/RTYPE_game/src/Rtype.cpp
    ../ECS/src/registry.cpp
    ../ECS/src/FollowPath.cpp
)

set(INCLUDE_DIRECTORY
    ../ECS/include/
    ../ECS/include/components
    ../utils
    graphics/
    graphics/SFML/include/
    games/
    games/RTYPE_game/include/
)
include_directories(${INCLUDE_DIRECTORY})

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x  
)
FetchContent_MakeAvailable(SFML)

# equivalent to -fPIC flag on Makefile
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

ADD_LIBRARY(sfml SHARED ${SFML_SOURCE_FILES})
ADD_LIBRARY(rtype SHARED ${RTYPE_SOURCE_FILES})
target_link_libraries(sfml PRIVATE sfml-graphics)

