# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sethbalodi/CODE/project3-shashwb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sethbalodi/CODE/project3-shashwb/_build

# Utility rule file for vtray_automoc.

# Include the progress variables for this target.
include CMakeFiles/vtray_automoc.dir/progress.make

CMakeFiles/vtray_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/sethbalodi/CODE/project3-shashwb/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target vtray"
	/usr/local/Cellar/cmake/3.7.2/bin/cmake -E cmake_autogen /Users/sethbalodi/CODE/project3-shashwb/_build/CMakeFiles/vtray_automoc.dir/ ""

vtray_automoc: CMakeFiles/vtray_automoc
vtray_automoc: CMakeFiles/vtray_automoc.dir/build.make

.PHONY : vtray_automoc

# Rule to build all files generated by this target.
CMakeFiles/vtray_automoc.dir/build: vtray_automoc

.PHONY : CMakeFiles/vtray_automoc.dir/build

CMakeFiles/vtray_automoc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vtray_automoc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vtray_automoc.dir/clean

CMakeFiles/vtray_automoc.dir/depend:
	cd /Users/sethbalodi/CODE/project3-shashwb/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sethbalodi/CODE/project3-shashwb /Users/sethbalodi/CODE/project3-shashwb /Users/sethbalodi/CODE/project3-shashwb/_build /Users/sethbalodi/CODE/project3-shashwb/_build /Users/sethbalodi/CODE/project3-shashwb/_build/CMakeFiles/vtray_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vtray_automoc.dir/depend

