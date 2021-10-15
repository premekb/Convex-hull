cmake_minimum_required(VERSION 3.19)
project(semestralka)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(core-files
    point.hpp
    svg_helper.cpp
    svg_helper.h)

add_executable(semestralka main.cpp svg_helper.cpp svg_helper.h points_generator.cpp points_generator.h convex_hull_solver.cpp convex_hull_solver.h)