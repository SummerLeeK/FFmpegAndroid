# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Users/apple/Library/Android/sdk/cmake/3.10.2.4988404/bin/cmake

# The command to remove a file.
RM = /Users/apple/Library/Android/sdk/cmake/3.10.2.4988404/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv

# Include any dependencies generated for this target.
include CMakeFiles/convert.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/convert.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/convert.dir/flags.make

CMakeFiles/convert.dir/util/convert.cc.o: CMakeFiles/convert.dir/flags.make
CMakeFiles/convert.dir/util/convert.cc.o: util/convert.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/convert.dir/util/convert.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/convert.dir/util/convert.cc.o -c /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/util/convert.cc

CMakeFiles/convert.dir/util/convert.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/convert.dir/util/convert.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/util/convert.cc > CMakeFiles/convert.dir/util/convert.cc.i

CMakeFiles/convert.dir/util/convert.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/convert.dir/util/convert.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/util/convert.cc -o CMakeFiles/convert.dir/util/convert.cc.s

CMakeFiles/convert.dir/util/convert.cc.o.requires:

.PHONY : CMakeFiles/convert.dir/util/convert.cc.o.requires

CMakeFiles/convert.dir/util/convert.cc.o.provides: CMakeFiles/convert.dir/util/convert.cc.o.requires
	$(MAKE) -f CMakeFiles/convert.dir/build.make CMakeFiles/convert.dir/util/convert.cc.o.provides.build
.PHONY : CMakeFiles/convert.dir/util/convert.cc.o.provides

CMakeFiles/convert.dir/util/convert.cc.o.provides.build: CMakeFiles/convert.dir/util/convert.cc.o


# Object files for target convert
convert_OBJECTS = \
"CMakeFiles/convert.dir/util/convert.cc.o"

# External object files for target convert
convert_EXTERNAL_OBJECTS =

convert: CMakeFiles/convert.dir/util/convert.cc.o
convert: CMakeFiles/convert.dir/build.make
convert: libyuv.a
convert: CMakeFiles/convert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable convert"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/convert.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/convert.dir/build: convert

.PHONY : CMakeFiles/convert.dir/build

CMakeFiles/convert.dir/requires: CMakeFiles/convert.dir/util/convert.cc.o.requires

.PHONY : CMakeFiles/convert.dir/requires

CMakeFiles/convert.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/convert.dir/cmake_clean.cmake
.PHONY : CMakeFiles/convert.dir/clean

CMakeFiles/convert.dir/depend:
	cd /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv /Users/apple/AndroidStudioProjects/FFmpegAndroid/app/src/main/cpp/libyuv/CMakeFiles/convert.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/convert.dir/depend
