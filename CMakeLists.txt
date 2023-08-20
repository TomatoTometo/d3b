cmake_minimum_required(VERSION 3.20)

cmake_policy(SET CMP0144 NEW)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(d3b)

set(EXTERNAL_SOURCE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(EXTERNAL_BINARY_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/external")

include(cmake/setup_boost.cmake)

add_subdirectory(d3b)


# add the executable
add_executable(d3b main.cpp)

target_link_libraries(d3b options d3b-manager)

