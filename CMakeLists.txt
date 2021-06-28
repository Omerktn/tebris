cmake_minimum_required (VERSION 3.8)

project(tebris VERSION 0.0.1)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable (tebris src/main.cpp src/engine.cpp)

#add_subdirectory("SFML")

target_link_libraries(tebris sfml-graphics sfml-audio sfml-window sfml-system)
