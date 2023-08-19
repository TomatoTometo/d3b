cmake_minimum_required(VERSION 3.20)

cmake_policy(SET CMP0144 NEW)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(d3b)

add_subdirectory(external)

# add the executable
add_executable(d3b main.cpp)

# add_dependencies(d3b unzip_target)



