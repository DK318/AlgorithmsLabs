# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/dk318/clion-2019.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/dk318/clion-2019.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dk318/AlgorithmsLabs/Lab3/min_dsu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/min_dsu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/min_dsu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/min_dsu.dir/flags.make

CMakeFiles/min_dsu.dir/main.cpp.o: CMakeFiles/min_dsu.dir/flags.make
CMakeFiles/min_dsu.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/min_dsu.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/min_dsu.dir/main.cpp.o -c /home/dk318/AlgorithmsLabs/Lab3/min_dsu/main.cpp

CMakeFiles/min_dsu.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/min_dsu.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dk318/AlgorithmsLabs/Lab3/min_dsu/main.cpp > CMakeFiles/min_dsu.dir/main.cpp.i

CMakeFiles/min_dsu.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/min_dsu.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dk318/AlgorithmsLabs/Lab3/min_dsu/main.cpp -o CMakeFiles/min_dsu.dir/main.cpp.s

# Object files for target min_dsu
min_dsu_OBJECTS = \
"CMakeFiles/min_dsu.dir/main.cpp.o"

# External object files for target min_dsu
min_dsu_EXTERNAL_OBJECTS =

min_dsu: CMakeFiles/min_dsu.dir/main.cpp.o
min_dsu: CMakeFiles/min_dsu.dir/build.make
min_dsu: CMakeFiles/min_dsu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable min_dsu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/min_dsu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/min_dsu.dir/build: min_dsu

.PHONY : CMakeFiles/min_dsu.dir/build

CMakeFiles/min_dsu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/min_dsu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/min_dsu.dir/clean

CMakeFiles/min_dsu.dir/depend:
	cd /home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dk318/AlgorithmsLabs/Lab3/min_dsu /home/dk318/AlgorithmsLabs/Lab3/min_dsu /home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug /home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug /home/dk318/AlgorithmsLabs/Lab3/min_dsu/cmake-build-debug/CMakeFiles/min_dsu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/min_dsu.dir/depend

