cmake_minimum_required(VERSION 3.31.6)

project(sorting_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(include)


add_library(parameters_lib SHARED src/Parameters.cpp)


add_executable(${PROJECT_NAME}
        src/main.cpp)

target_link_libraries(${PROJECT_NAME} parameters_lib)