cmake_minimum_required(VERSION 3.0)
project(physics3)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable target
add_executable(program main.c)

# Link SDL2 libraries
target_link_libraries(program ${SDL2_LIBRARIES} SDL2_gfx m)
