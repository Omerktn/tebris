cmake_minimum_required (VERSION 3.8)

project(tebris VERSION 0.0.1)

set (CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -std=c++20")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable (tebris src/main.cpp src/engine.cpp src/game.cpp)

set_target_properties(tebris PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(tebris sfml-graphics sfml-audio sfml-window sfml-system)
