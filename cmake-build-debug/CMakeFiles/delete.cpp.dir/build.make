# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /afs/asu.edu/users/m/r/l/mrlunt/CSE310

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/asu.edu/users/m/r/l/mrlunt/CSE310/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/delete.cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/delete.cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/delete.cpp.dir/flags.make

CMakeFiles/delete.cpp.dir/delete.cpp.o: CMakeFiles/delete.cpp.dir/flags.make
CMakeFiles/delete.cpp.dir/delete.cpp.o: ../delete.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/asu.edu/users/m/r/l/mrlunt/CSE310/cmake-build-debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/delete.cpp.dir/delete.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/delete.cpp.dir/delete.cpp.o -c /afs/asu.edu/users/m/r/l/mrlunt/CSE310/delete.cpp

CMakeFiles/delete.cpp.dir/delete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/delete.cpp.dir/delete.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /afs/asu.edu/users/m/r/l/mrlunt/CSE310/delete.cpp > CMakeFiles/delete.cpp.dir/delete.cpp.i

CMakeFiles/delete.cpp.dir/delete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/delete.cpp.dir/delete.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /afs/asu.edu/users/m/r/l/mrlunt/CSE310/delete.cpp -o CMakeFiles/delete.cpp.dir/delete.cpp.s

CMakeFiles/delete.cpp.dir/delete.cpp.o.requires:
.PHONY : CMakeFiles/delete.cpp.dir/delete.cpp.o.requires

CMakeFiles/delete.cpp.dir/delete.cpp.o.provides: CMakeFiles/delete.cpp.dir/delete.cpp.o.requires
	$(MAKE) -f CMakeFiles/delete.cpp.dir/build.make CMakeFiles/delete.cpp.dir/delete.cpp.o.provides.build
.PHONY : CMakeFiles/delete.cpp.dir/delete.cpp.o.provides

CMakeFiles/delete.cpp.dir/delete.cpp.o.provides.build: CMakeFiles/delete.cpp.dir/delete.cpp.o

# Object files for target delete.cpp
delete_cpp_OBJECTS = \
"CMakeFiles/delete.cpp.dir/delete.cpp.o"

# External object files for target delete.cpp
delete_cpp_EXTERNAL_OBJECTS =

delete.cpp: CMakeFiles/delete.cpp.dir/delete.cpp.o
delete.cpp: CMakeFiles/delete.cpp.dir/build.make
delete.cpp: CMakeFiles/delete.cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable delete.cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/delete.cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/delete.cpp.dir/build: delete.cpp
.PHONY : CMakeFiles/delete.cpp.dir/build

CMakeFiles/delete.cpp.dir/requires: CMakeFiles/delete.cpp.dir/delete.cpp.o.requires
.PHONY : CMakeFiles/delete.cpp.dir/requires

CMakeFiles/delete.cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/delete.cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/delete.cpp.dir/clean

CMakeFiles/delete.cpp.dir/depend:
	cd /afs/asu.edu/users/m/r/l/mrlunt/CSE310/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/asu.edu/users/m/r/l/mrlunt/CSE310 /afs/asu.edu/users/m/r/l/mrlunt/CSE310 /afs/asu.edu/users/m/r/l/mrlunt/CSE310/cmake-build-debug /afs/asu.edu/users/m/r/l/mrlunt/CSE310/cmake-build-debug /afs/asu.edu/users/m/r/l/mrlunt/CSE310/cmake-build-debug/CMakeFiles/delete.cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/delete.cpp.dir/depend

