cmake_minimum_required(VERSION 3.10)
project(qr-gen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(hdr)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(CMAKE_CXX_FLAGS "-Wall -g")

include_directories(${GTK3_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cc)

# Add the executable target
add_executable(qr-gen ${SOURCES})

# Link GTK3 to the executable
target_link_libraries(qr-gen ${GTK3_LIBRARIES})

# Additional flags (if needed)
target_compile_options(qr-gen PRIVATE ${GTK3_CFLAGS_OTHER})

