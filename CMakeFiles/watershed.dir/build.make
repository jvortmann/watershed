# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.4

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joao/Desktop/Watershed/Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joao/Desktop/Watershed/Code

# Include any dependencies generated for this target.
include CMakeFiles/watershed.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/watershed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/watershed.dir/flags.make

CMakeFiles/watershed.dir/depend.make.mark: CMakeFiles/watershed.dir/flags.make
CMakeFiles/watershed.dir/depend.make.mark: watershed.cxx

CMakeFiles/watershed.dir/watershed.o: CMakeFiles/watershed.dir/flags.make
CMakeFiles/watershed.dir/watershed.o: watershed.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/joao/Desktop/Watershed/Code/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/watershed.dir/watershed.o"
	/usr/bin/c++   $(CXX_FLAGS) -o CMakeFiles/watershed.dir/watershed.o -c /Users/joao/Desktop/Watershed/Code/watershed.cxx

CMakeFiles/watershed.dir/watershed.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/watershed.dir/watershed.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/joao/Desktop/Watershed/Code/watershed.cxx > CMakeFiles/watershed.dir/watershed.i

CMakeFiles/watershed.dir/watershed.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/watershed.dir/watershed.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/joao/Desktop/Watershed/Code/watershed.cxx -o CMakeFiles/watershed.dir/watershed.s

CMakeFiles/watershed.dir/watershed.o.requires:

CMakeFiles/watershed.dir/watershed.o.provides: CMakeFiles/watershed.dir/watershed.o.requires
	$(MAKE) -f CMakeFiles/watershed.dir/build.make CMakeFiles/watershed.dir/watershed.o.provides.build

CMakeFiles/watershed.dir/watershed.o.provides.build: CMakeFiles/watershed.dir/watershed.o

CMakeFiles/watershed.dir/depend: CMakeFiles/watershed.dir/depend.make.mark

CMakeFiles/watershed.dir/depend.make.mark:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --magenta --bold "Scanning dependencies of target watershed"
	cd /Users/joao/Desktop/Watershed/Code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joao/Desktop/Watershed/Code /Users/joao/Desktop/Watershed/Code /Users/joao/Desktop/Watershed/Code /Users/joao/Desktop/Watershed/Code /Users/joao/Desktop/Watershed/Code/CMakeFiles/watershed.dir/DependInfo.cmake

# Object files for target watershed
watershed_OBJECTS = \
"CMakeFiles/watershed.dir/watershed.o"

# External object files for target watershed
watershed_EXTERNAL_OBJECTS =

watershed: CMakeFiles/watershed.dir/watershed.o
watershed: CMakeFiles/watershed.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable watershed"
	$(CMAKE_COMMAND) -P CMakeFiles/watershed.dir/cmake_clean_target.cmake
	/usr/bin/c++      -ftemplate-depth-50 -no-cpp-precomp -Wno-long-double -O3 -DNDEBUG -headerpad_max_install_names -fPIC   $(watershed_OBJECTS) $(watershed_EXTERNAL_OBJECTS)  -o watershed  -L/usr/local/lib/InsightToolkit -lITKIO -lITKAlgorithms -lITKBasicFilters -lITKStatistics -lITKNrrdIO -litkgdcm -litkjpeg12 -litkjpeg16 -litkopenjpeg -litkpng -litktiff -litkjpeg8 -lITKSpatialObject -lITKMetaIO -lITKDICOMParser -lITKEXPAT -lITKniftiio -lITKznz -litkzlib -lITKNumerics -lITKCommon -litkvnl_inst -litkvnl_algo -litkv3p_netlib -litkvnl -litkvcl -lm -litksys -lpthread -lm 

# Rule to build all files generated by this target.
CMakeFiles/watershed.dir/build: watershed

CMakeFiles/watershed.dir/requires: CMakeFiles/watershed.dir/watershed.o.requires

CMakeFiles/watershed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/watershed.dir/cmake_clean.cmake

