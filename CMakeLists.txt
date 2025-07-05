cmake_minimum_required(VERSION 3.10)

# Project name and version
project(legacy_embedded_modernization VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optionally set compile warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Define source files
set(SOURCES
    main.cpp
    system.cpp
    sensor.cpp
    controller.cpp
)

# Define the executable
add_executable(legacy_app ${SOURCES})

# Installation (optional)
install(TARGETS legacy_app DESTINATION bin)
