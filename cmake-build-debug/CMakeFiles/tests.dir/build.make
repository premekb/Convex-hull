# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/premekbelka/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/211.7628.27/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/premekbelka/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/211.7628.27/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests.dir/flags.make

CMakeFiles/tests.dir/tests/quickhull_test.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/tests/quickhull_test.cpp.o: ../tests/quickhull_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tests.dir/tests/quickhull_test.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/tests/quickhull_test.cpp.o -c "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/tests/quickhull_test.cpp"

CMakeFiles/tests.dir/tests/quickhull_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/tests/quickhull_test.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/tests/quickhull_test.cpp" > CMakeFiles/tests.dir/tests/quickhull_test.cpp.i

CMakeFiles/tests.dir/tests/quickhull_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/tests/quickhull_test.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/tests/quickhull_test.cpp" -o CMakeFiles/tests.dir/tests/quickhull_test.cpp.s

CMakeFiles/tests.dir/tests/tests_main.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/tests/tests_main.cpp.o: ../tests/tests_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tests.dir/tests/tests_main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/tests/tests_main.cpp.o -c "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/tests/tests_main.cpp"

CMakeFiles/tests.dir/tests/tests_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/tests/tests_main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/tests/tests_main.cpp" > CMakeFiles/tests.dir/tests/tests_main.cpp.i

CMakeFiles/tests.dir/tests/tests_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/tests/tests_main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/tests/tests_main.cpp" -o CMakeFiles/tests.dir/tests/tests_main.cpp.s

CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.o: ../quickhull_single_thead/convex_hull_solver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.o -c "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/quickhull_single_thead/convex_hull_solver.cpp"

CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/quickhull_single_thead/convex_hull_solver.cpp" > CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.i

CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/quickhull_single_thead/convex_hull_solver.cpp" -o CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.s

CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.o: ../quickhull_parallel/convex_hull_solver_parallel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.o -c "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/quickhull_parallel/convex_hull_solver_parallel.cpp"

CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/quickhull_parallel/convex_hull_solver_parallel.cpp" > CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.i

CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/quickhull_parallel/convex_hull_solver_parallel.cpp" -o CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.s

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/tests/quickhull_test.cpp.o" \
"CMakeFiles/tests.dir/tests/tests_main.cpp.o" \
"CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.o" \
"CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests: CMakeFiles/tests.dir/tests/quickhull_test.cpp.o
tests: CMakeFiles/tests.dir/tests/tests_main.cpp.o
tests: CMakeFiles/tests.dir/quickhull_single_thead/convex_hull_solver.cpp.o
tests: CMakeFiles/tests.dir/quickhull_parallel/convex_hull_solver_parallel.cpp.o
tests: CMakeFiles/tests.dir/build.make
tests: CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests.dir/build: tests

.PHONY : CMakeFiles/tests.dir/build

CMakeFiles/tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests.dir/clean

CMakeFiles/tests.dir/depend:
	cd "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka" "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka" "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug" "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug" "/Users/premekbelka/Documents/Semestr 3/PJC/semestralka/pjc-semestralka/cmake-build-debug/CMakeFiles/tests.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/tests.dir/depend

