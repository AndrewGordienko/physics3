<<<<<<< HEAD
cmake_minimum_required(VERSION 3.12)
project(physics3 C)

set(CMAKE_C_STANDARD 11)
=======
cmake_minimum_required(VERSION 3.0)
project(physics3)
>>>>>>> 1560941e3d478972062cbebf5b4f85964d4d34e5

# Find SDL2 package
find_package(SDL2 REQUIRED)

<<<<<<< HEAD
# Add executable target
add_executable(program main.c orbiting_body.c gravitating_body.c)

# Include SDL2 directories
target_include_directories(program PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(program PRIVATE ${SDL2_LIBRARIES} SDL2_gfx m)
=======
# Add include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable target
add_executable(program main.c)

# Link SDL2 libraries
target_link_libraries(program ${SDL2_LIBRARIES} SDL2_gfx m)
>>>>>>> 1560941e3d478972062cbebf5b4f85964d4d34e5
