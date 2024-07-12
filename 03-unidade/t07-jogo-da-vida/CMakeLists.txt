cmake_minimum_required(VERSION 3.5)
project(glife)

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== SETTING VARIABLES ===#
# Compiling flags
set(GCC_COMPILE_FLAGS "-Wall")
#set(PREPROCESSING_FLAGS  "-D PRINT")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}")

#=== Main App ===
include_directories(init src lib)

add_executable(glife 
    src/main.cpp
    src/life.cpp
    src/config.cpp
    lib/canvas.cpp
    lib/lodepng.cpp
    init/ini_parser.cpp
)

#define C++17 as the standard.
target_compile_features(glife PUBLIC cxx_std_17)