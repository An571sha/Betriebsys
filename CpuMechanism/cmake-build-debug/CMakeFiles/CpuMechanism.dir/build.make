# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/animeshSharma/Betriebsys/CpuMechanism

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CpuMechanism.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CpuMechanism.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CpuMechanism.dir/flags.make

CMakeFiles/CpuMechanism.dir/main.c.o: CMakeFiles/CpuMechanism.dir/flags.make
CMakeFiles/CpuMechanism.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CpuMechanism.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CpuMechanism.dir/main.c.o   -c /Users/animeshSharma/Betriebsys/CpuMechanism/main.c

CMakeFiles/CpuMechanism.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CpuMechanism.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/animeshSharma/Betriebsys/CpuMechanism/main.c > CMakeFiles/CpuMechanism.dir/main.c.i

CMakeFiles/CpuMechanism.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CpuMechanism.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/animeshSharma/Betriebsys/CpuMechanism/main.c -o CMakeFiles/CpuMechanism.dir/main.c.s

# Object files for target CpuMechanism
CpuMechanism_OBJECTS = \
"CMakeFiles/CpuMechanism.dir/main.c.o"

# External object files for target CpuMechanism
CpuMechanism_EXTERNAL_OBJECTS =

CpuMechanism: CMakeFiles/CpuMechanism.dir/main.c.o
CpuMechanism: CMakeFiles/CpuMechanism.dir/build.make
CpuMechanism: CMakeFiles/CpuMechanism.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CpuMechanism"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CpuMechanism.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CpuMechanism.dir/build: CpuMechanism

.PHONY : CMakeFiles/CpuMechanism.dir/build

CMakeFiles/CpuMechanism.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CpuMechanism.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CpuMechanism.dir/clean

CMakeFiles/CpuMechanism.dir/depend:
	cd /Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/animeshSharma/Betriebsys/CpuMechanism /Users/animeshSharma/Betriebsys/CpuMechanism /Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug /Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug /Users/animeshSharma/Betriebsys/CpuMechanism/cmake-build-debug/CMakeFiles/CpuMechanism.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CpuMechanism.dir/depend

