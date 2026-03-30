cmake_minimum_required(VERSION 3.31.6)

project(sorting_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp)