cmake_minimum_required(VERSION 3.10)
project(FlapGenius)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Include the header files
include_directories(include)

# Add the executable
add_executable(FlapGenius src/main.c)
