# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build

# Include any dependencies generated for this target.
include src/opening/CMakeFiles/DeceideOverOpening.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/opening/CMakeFiles/DeceideOverOpening.dir/compiler_depend.make

# Include the progress variables for this target.
include src/opening/CMakeFiles/DeceideOverOpening.dir/progress.make

# Include the compile flags for this target's objects.
include src/opening/CMakeFiles/DeceideOverOpening.dir/flags.make

src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj: src/opening/CMakeFiles/DeceideOverOpening.dir/flags.make
src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj: src/opening/CMakeFiles/DeceideOverOpening.dir/includes_CXX.rsp
src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj: C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/src/opening/OpeningMain.cpp
src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj: src/opening/CMakeFiles/DeceideOverOpening.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj"
	cd C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening && C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj -MF CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj.d -o CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj -c C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/src/opening/OpeningMain.cpp

src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.i"
	cd C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening && C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/src/opening/OpeningMain.cpp > CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.i

src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.s"
	cd C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening && C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/src/opening/OpeningMain.cpp -o CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.s

# Object files for target DeceideOverOpening
DeceideOverOpening_OBJECTS = \
"CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj"

# External object files for target DeceideOverOpening
DeceideOverOpening_EXTERNAL_OBJECTS =

src/opening/libDeceideOverOpening.a: src/opening/CMakeFiles/DeceideOverOpening.dir/OpeningMain.cpp.obj
src/opening/libDeceideOverOpening.a: src/opening/CMakeFiles/DeceideOverOpening.dir/build.make
src/opening/libDeceideOverOpening.a: src/opening/CMakeFiles/DeceideOverOpening.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libDeceideOverOpening.a"
	cd C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening && $(CMAKE_COMMAND) -P CMakeFiles/DeceideOverOpening.dir/cmake_clean_target.cmake
	cd C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DeceideOverOpening.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/opening/CMakeFiles/DeceideOverOpening.dir/build: src/opening/libDeceideOverOpening.a
.PHONY : src/opening/CMakeFiles/DeceideOverOpening.dir/build

src/opening/CMakeFiles/DeceideOverOpening.dir/clean:
	cd C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening && $(CMAKE_COMMAND) -P CMakeFiles/DeceideOverOpening.dir/cmake_clean.cmake
.PHONY : src/opening/CMakeFiles/DeceideOverOpening.dir/clean

src/opening/CMakeFiles/DeceideOverOpening.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/src/opening C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening C:/Users/andre/OneDrive/Desktop/Closedfish/closedfish/build/src/opening/CMakeFiles/DeceideOverOpening.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/opening/CMakeFiles/DeceideOverOpening.dir/depend

