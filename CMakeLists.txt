cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(myProject)

# add the executable
add_executable(myProject main.cpp)

target_link_libraries(myProject PUBLIC
  phrases
  # spanish
  # english
)

# add_subdirectory(languages)
add_subdirectory(common)
