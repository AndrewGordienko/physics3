cmake_minimum_required(VERSION 3.12)
project(physics3 C)

set(CMAKE_C_STANDARD 11)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add include directories
include_directories(include)

# Add executable target
add_executable(program src/main.c src/gravitating_body.c src/orbiting_body.c)

# Include SDL2 directories
target_include_directories(program PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(program PRIVATE ${SDL2_LIBRARIES} SDL2_gfx m)
