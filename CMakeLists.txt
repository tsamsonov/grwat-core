cmake_minimum_required(VERSION 3.15)
project(grwat_core)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
    grwat_core.cpp
    main.cpp
)

add_executable(grwat_core ${SOURCES})
