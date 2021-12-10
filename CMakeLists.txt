cmake_minimum_required(VERSION 3.19)
project(semestralka)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

add_executable(semestralka main.cpp svg_helper.cpp svg_helper.h points_generator.cpp points_generator.h quickhull_single_thead/convex_hull_solver.cpp quickhull_single_thead/convex_hull_solver.h cmdline/config.hpp point.cpp quickhull_parallel/convex_hull_solver_parallel.cpp quickhull_parallel/convex_hull_solver_parallel.hpp)

add_executable(tests tests/quickhull_test.cpp tests/tests_main.cpp quickhull_single_thead/convex_hull_solver.cpp quickhull_single_thead/convex_hull_solver.h quickhull_parallel/convex_hull_solver_parallel.cpp quickhull_parallel/convex_hull_solver_parallel.hpp)
enable_testing()
add_test(NAME tests COMMAND tests)