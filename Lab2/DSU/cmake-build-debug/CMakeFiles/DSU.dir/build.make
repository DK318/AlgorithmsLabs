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
CMAKE_SOURCE_DIR = /home/dk318/AlgorithmsLabs/DSU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dk318/AlgorithmsLabs/DSU/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DSU.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DSU.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DSU.dir/flags.make

CMakeFiles/DSU.dir/main.cpp.o: CMakeFiles/DSU.dir/flags.make
CMakeFiles/DSU.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dk318/AlgorithmsLabs/DSU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DSU.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DSU.dir/main.cpp.o -c /home/dk318/AlgorithmsLabs/DSU/main.cpp

CMakeFiles/DSU.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DSU.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dk318/AlgorithmsLabs/DSU/main.cpp > CMakeFiles/DSU.dir/main.cpp.i

CMakeFiles/DSU.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DSU.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dk318/AlgorithmsLabs/DSU/main.cpp -o CMakeFiles/DSU.dir/main.cpp.s

# Object files for target DSU
DSU_OBJECTS = \
"CMakeFiles/DSU.dir/main.cpp.o"

# External object files for target DSU
DSU_EXTERNAL_OBJECTS =

DSU: CMakeFiles/DSU.dir/main.cpp.o
DSU: CMakeFiles/DSU.dir/build.make
DSU: CMakeFiles/DSU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dk318/AlgorithmsLabs/DSU/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DSU"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DSU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DSU.dir/build: DSU

.PHONY : CMakeFiles/DSU.dir/build

CMakeFiles/DSU.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DSU.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DSU.dir/clean

CMakeFiles/DSU.dir/depend:
	cd /home/dk318/AlgorithmsLabs/DSU/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dk318/AlgorithmsLabs/DSU /home/dk318/AlgorithmsLabs/DSU /home/dk318/AlgorithmsLabs/DSU/cmake-build-debug /home/dk318/AlgorithmsLabs/DSU/cmake-build-debug /home/dk318/AlgorithmsLabs/DSU/cmake-build-debug/CMakeFiles/DSU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DSU.dir/depend
