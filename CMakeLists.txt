cmake_minimum_required(VERSION 3.0)
project(Gra)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Include directories
include_directories(include)

# Collect all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(giera ${SOURCES})
# Link SFML
target_link_libraries(giera sfml-system sfml-window sfml-graphics)
