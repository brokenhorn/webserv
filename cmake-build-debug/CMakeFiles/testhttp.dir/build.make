# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vmaricru/Desktop/testhttp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vmaricru/Desktop/testhttp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/testhttp.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/testhttp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testhttp.dir/flags.make

CMakeFiles/testhttp.dir/start.cpp.o: CMakeFiles/testhttp.dir/flags.make
CMakeFiles/testhttp.dir/start.cpp.o: ../start.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testhttp.dir/start.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testhttp.dir/start.cpp.o -c /Users/vmaricru/Desktop/testhttp/start.cpp

CMakeFiles/testhttp.dir/start.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testhttp.dir/start.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vmaricru/Desktop/testhttp/start.cpp > CMakeFiles/testhttp.dir/start.cpp.i

CMakeFiles/testhttp.dir/start.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testhttp.dir/start.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vmaricru/Desktop/testhttp/start.cpp -o CMakeFiles/testhttp.dir/start.cpp.s

CMakeFiles/testhttp.dir/Server.cpp.o: CMakeFiles/testhttp.dir/flags.make
CMakeFiles/testhttp.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testhttp.dir/Server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testhttp.dir/Server.cpp.o -c /Users/vmaricru/Desktop/testhttp/Server.cpp

CMakeFiles/testhttp.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testhttp.dir/Server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vmaricru/Desktop/testhttp/Server.cpp > CMakeFiles/testhttp.dir/Server.cpp.i

CMakeFiles/testhttp.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testhttp.dir/Server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vmaricru/Desktop/testhttp/Server.cpp -o CMakeFiles/testhttp.dir/Server.cpp.s

CMakeFiles/testhttp.dir/ServerUnit.cpp.o: CMakeFiles/testhttp.dir/flags.make
CMakeFiles/testhttp.dir/ServerUnit.cpp.o: ../ServerUnit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testhttp.dir/ServerUnit.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testhttp.dir/ServerUnit.cpp.o -c /Users/vmaricru/Desktop/testhttp/ServerUnit.cpp

CMakeFiles/testhttp.dir/ServerUnit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testhttp.dir/ServerUnit.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vmaricru/Desktop/testhttp/ServerUnit.cpp > CMakeFiles/testhttp.dir/ServerUnit.cpp.i

CMakeFiles/testhttp.dir/ServerUnit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testhttp.dir/ServerUnit.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vmaricru/Desktop/testhttp/ServerUnit.cpp -o CMakeFiles/testhttp.dir/ServerUnit.cpp.s

CMakeFiles/testhttp.dir/Request.cpp.o: CMakeFiles/testhttp.dir/flags.make
CMakeFiles/testhttp.dir/Request.cpp.o: ../Request.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/testhttp.dir/Request.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testhttp.dir/Request.cpp.o -c /Users/vmaricru/Desktop/testhttp/Request.cpp

CMakeFiles/testhttp.dir/Request.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testhttp.dir/Request.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vmaricru/Desktop/testhttp/Request.cpp > CMakeFiles/testhttp.dir/Request.cpp.i

CMakeFiles/testhttp.dir/Request.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testhttp.dir/Request.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vmaricru/Desktop/testhttp/Request.cpp -o CMakeFiles/testhttp.dir/Request.cpp.s

CMakeFiles/testhttp.dir/parser.cpp.o: CMakeFiles/testhttp.dir/flags.make
CMakeFiles/testhttp.dir/parser.cpp.o: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/testhttp.dir/parser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testhttp.dir/parser.cpp.o -c /Users/vmaricru/Desktop/testhttp/parser.cpp

CMakeFiles/testhttp.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testhttp.dir/parser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vmaricru/Desktop/testhttp/parser.cpp > CMakeFiles/testhttp.dir/parser.cpp.i

CMakeFiles/testhttp.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testhttp.dir/parser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vmaricru/Desktop/testhttp/parser.cpp -o CMakeFiles/testhttp.dir/parser.cpp.s

# Object files for target testhttp
testhttp_OBJECTS = \
"CMakeFiles/testhttp.dir/start.cpp.o" \
"CMakeFiles/testhttp.dir/Server.cpp.o" \
"CMakeFiles/testhttp.dir/ServerUnit.cpp.o" \
"CMakeFiles/testhttp.dir/Request.cpp.o" \
"CMakeFiles/testhttp.dir/parser.cpp.o"

# External object files for target testhttp
testhttp_EXTERNAL_OBJECTS =

testhttp: CMakeFiles/testhttp.dir/start.cpp.o
testhttp: CMakeFiles/testhttp.dir/Server.cpp.o
testhttp: CMakeFiles/testhttp.dir/ServerUnit.cpp.o
testhttp: CMakeFiles/testhttp.dir/Request.cpp.o
testhttp: CMakeFiles/testhttp.dir/parser.cpp.o
testhttp: CMakeFiles/testhttp.dir/build.make
testhttp: CMakeFiles/testhttp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable testhttp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testhttp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testhttp.dir/build: testhttp
.PHONY : CMakeFiles/testhttp.dir/build

CMakeFiles/testhttp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testhttp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testhttp.dir/clean

CMakeFiles/testhttp.dir/depend:
	cd /Users/vmaricru/Desktop/testhttp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vmaricru/Desktop/testhttp /Users/vmaricru/Desktop/testhttp /Users/vmaricru/Desktop/testhttp/cmake-build-debug /Users/vmaricru/Desktop/testhttp/cmake-build-debug /Users/vmaricru/Desktop/testhttp/cmake-build-debug/CMakeFiles/testhttp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testhttp.dir/depend

