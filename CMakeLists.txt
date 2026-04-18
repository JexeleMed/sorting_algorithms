cmake_minimum_required(VERSION 3.31.6)
project(sorting_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(include)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/Parameters.cpp")
    message(STATUS "Developer mode: Compiling from source (src/Parameters.cpp)")
    add_executable(${PROJECT_NAME} src/main.cpp src/Parameters.cpp)

else()
    message(STATUS "Production mode: Looking for compiled library 'parameters'")

    add_executable(${PROJECT_NAME} src/main.cpp)

    find_library(PARAMETERS_LIB
            NAMES parameters
            PATHS "${CMAKE_CURRENT_SOURCE_DIR}/external"
            REQUIRED
    )

    if(PARAMETERS_LIB)
        message(STATUS "Library found: ${PARAMETERS_LIB}")
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PARAMETERS_LIB})
    endif()
endif()