# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alarm/Programming/ed65

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alarm/Programming/ed65/build

# Include any dependencies generated for this target.
include CMakeFiles/ed65.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ed65.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ed65.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ed65.dir/flags.make

CMakeFiles/ed65.dir/src/main.cpp.o: CMakeFiles/ed65.dir/flags.make
CMakeFiles/ed65.dir/src/main.cpp.o: /home/alarm/Programming/ed65/src/main.cpp
CMakeFiles/ed65.dir/src/main.cpp.o: CMakeFiles/ed65.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alarm/Programming/ed65/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ed65.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ed65.dir/src/main.cpp.o -MF CMakeFiles/ed65.dir/src/main.cpp.o.d -o CMakeFiles/ed65.dir/src/main.cpp.o -c /home/alarm/Programming/ed65/src/main.cpp

CMakeFiles/ed65.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ed65.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alarm/Programming/ed65/src/main.cpp > CMakeFiles/ed65.dir/src/main.cpp.i

CMakeFiles/ed65.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ed65.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alarm/Programming/ed65/src/main.cpp -o CMakeFiles/ed65.dir/src/main.cpp.s

CMakeFiles/ed65.dir/src/common.cpp.o: CMakeFiles/ed65.dir/flags.make
CMakeFiles/ed65.dir/src/common.cpp.o: /home/alarm/Programming/ed65/src/common.cpp
CMakeFiles/ed65.dir/src/common.cpp.o: CMakeFiles/ed65.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alarm/Programming/ed65/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ed65.dir/src/common.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ed65.dir/src/common.cpp.o -MF CMakeFiles/ed65.dir/src/common.cpp.o.d -o CMakeFiles/ed65.dir/src/common.cpp.o -c /home/alarm/Programming/ed65/src/common.cpp

CMakeFiles/ed65.dir/src/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ed65.dir/src/common.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alarm/Programming/ed65/src/common.cpp > CMakeFiles/ed65.dir/src/common.cpp.i

CMakeFiles/ed65.dir/src/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ed65.dir/src/common.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alarm/Programming/ed65/src/common.cpp -o CMakeFiles/ed65.dir/src/common.cpp.s

CMakeFiles/ed65.dir/src/text.cpp.o: CMakeFiles/ed65.dir/flags.make
CMakeFiles/ed65.dir/src/text.cpp.o: /home/alarm/Programming/ed65/src/text.cpp
CMakeFiles/ed65.dir/src/text.cpp.o: CMakeFiles/ed65.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alarm/Programming/ed65/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ed65.dir/src/text.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ed65.dir/src/text.cpp.o -MF CMakeFiles/ed65.dir/src/text.cpp.o.d -o CMakeFiles/ed65.dir/src/text.cpp.o -c /home/alarm/Programming/ed65/src/text.cpp

CMakeFiles/ed65.dir/src/text.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ed65.dir/src/text.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alarm/Programming/ed65/src/text.cpp > CMakeFiles/ed65.dir/src/text.cpp.i

CMakeFiles/ed65.dir/src/text.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ed65.dir/src/text.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alarm/Programming/ed65/src/text.cpp -o CMakeFiles/ed65.dir/src/text.cpp.s

# Object files for target ed65
ed65_OBJECTS = \
"CMakeFiles/ed65.dir/src/main.cpp.o" \
"CMakeFiles/ed65.dir/src/common.cpp.o" \
"CMakeFiles/ed65.dir/src/text.cpp.o"

# External object files for target ed65
ed65_EXTERNAL_OBJECTS =

bin/ed65: CMakeFiles/ed65.dir/src/main.cpp.o
bin/ed65: CMakeFiles/ed65.dir/src/common.cpp.o
bin/ed65: CMakeFiles/ed65.dir/src/text.cpp.o
bin/ed65: CMakeFiles/ed65.dir/build.make
bin/ed65: /usr/lib/libcurses.so
bin/ed65: /usr/lib/libform.so
bin/ed65: CMakeFiles/ed65.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alarm/Programming/ed65/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bin/ed65"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ed65.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ed65.dir/build: bin/ed65
.PHONY : CMakeFiles/ed65.dir/build

CMakeFiles/ed65.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ed65.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ed65.dir/clean

CMakeFiles/ed65.dir/depend:
	cd /home/alarm/Programming/ed65/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alarm/Programming/ed65 /home/alarm/Programming/ed65 /home/alarm/Programming/ed65/build /home/alarm/Programming/ed65/build /home/alarm/Programming/ed65/build/CMakeFiles/ed65.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ed65.dir/depend
