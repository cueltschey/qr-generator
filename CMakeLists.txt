cmake_minimum_required(VERSION 3.10)
project(qr-gen)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directories (hdr folder)
include_directories(hdr)

# Find the GTK+3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Add include directories for GTK
include_directories(${GTK3_INCLUDE_DIRS})

# Add the executable target
add_executable(grid_of_squares src/main.cc)

# Link GTK3 to the executable
target_link_libraries(grid_of_squares ${GTK3_LIBRARIES})

# Additional flags (if needed)
target_compile_options(grid_of_squares PRIVATE ${GTK3_CFLAGS_OTHER})

