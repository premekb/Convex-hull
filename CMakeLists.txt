cmake_minimum_required(VERSION 3.19)
project(semestralka)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(semestralka main.cpp svg_helper.cpp svg_helper.h points_generator.cpp points_generator.h quickhull_single_thead/convex_hull_solver.cpp quickhull_single_thead/convex_hull_solver.h cmdline/config.hpp point.cpp quickhull_parallel/convex_hull_solver_parallel.cpp quickhull_parallel/convex_hull_solver_parallel.hpp quickhull_parallel_future/convex_hull_solver_parallel_future.cpp quickhull_parallel_future/convex_hull_solver_parallel_future.hpp)

add_executable(tests tests/quickhull_test.cpp tests/tests_main.cpp quickhull_single_thead/convex_hull_solver.cpp quickhull_single_thead/convex_hull_solver.h quickhull_parallel/convex_hull_solver_parallel.cpp quickhull_parallel/convex_hull_solver_parallel.hpp quickhull_parallel_future/convex_hull_solver_parallel_future.cpp quickhull_parallel_future/convex_hull_solver_parallel_future.hpp)
enable_testing()
add_test(NAME tests COMMAND tests)

find_package(Threads REQUIRED)
target_link_libraries(semestralka Threads::Threads)