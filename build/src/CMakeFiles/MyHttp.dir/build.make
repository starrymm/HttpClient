# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/HttpClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/HttpClient/build

# Include any dependencies generated for this target.
include src/CMakeFiles/MyHttp.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/MyHttp.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/MyHttp.dir/flags.make

src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o: src/CMakeFiles/MyHttp.dir/flags.make
src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o: ../src/HttpClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/HttpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o"
	cd /root/HttpClient/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyHttp.dir/HttpClient.cpp.o -c /root/HttpClient/src/HttpClient.cpp

src/CMakeFiles/MyHttp.dir/HttpClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyHttp.dir/HttpClient.cpp.i"
	cd /root/HttpClient/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/HttpClient/src/HttpClient.cpp > CMakeFiles/MyHttp.dir/HttpClient.cpp.i

src/CMakeFiles/MyHttp.dir/HttpClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyHttp.dir/HttpClient.cpp.s"
	cd /root/HttpClient/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/HttpClient/src/HttpClient.cpp -o CMakeFiles/MyHttp.dir/HttpClient.cpp.s

src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.requires:

.PHONY : src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.requires

src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.provides: src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/MyHttp.dir/build.make src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.provides.build
.PHONY : src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.provides

src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.provides.build: src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o


src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o: src/CMakeFiles/MyHttp.dir/flags.make
src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o: ../src/HttpClientImp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/HttpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o"
	cd /root/HttpClient/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o -c /root/HttpClient/src/HttpClientImp.cpp

src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyHttp.dir/HttpClientImp.cpp.i"
	cd /root/HttpClient/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/HttpClient/src/HttpClientImp.cpp > CMakeFiles/MyHttp.dir/HttpClientImp.cpp.i

src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyHttp.dir/HttpClientImp.cpp.s"
	cd /root/HttpClient/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/HttpClient/src/HttpClientImp.cpp -o CMakeFiles/MyHttp.dir/HttpClientImp.cpp.s

src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.requires:

.PHONY : src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.requires

src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.provides: src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/MyHttp.dir/build.make src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.provides.build
.PHONY : src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.provides

src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.provides.build: src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o


# Object files for target MyHttp
MyHttp_OBJECTS = \
"CMakeFiles/MyHttp.dir/HttpClient.cpp.o" \
"CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o"

# External object files for target MyHttp
MyHttp_EXTERNAL_OBJECTS =

src/libMyHttp.so: src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o
src/libMyHttp.so: src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o
src/libMyHttp.so: src/CMakeFiles/MyHttp.dir/build.make
src/libMyHttp.so: src/CMakeFiles/MyHttp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/HttpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libMyHttp.so"
	cd /root/HttpClient/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyHttp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/MyHttp.dir/build: src/libMyHttp.so

.PHONY : src/CMakeFiles/MyHttp.dir/build

src/CMakeFiles/MyHttp.dir/requires: src/CMakeFiles/MyHttp.dir/HttpClient.cpp.o.requires
src/CMakeFiles/MyHttp.dir/requires: src/CMakeFiles/MyHttp.dir/HttpClientImp.cpp.o.requires

.PHONY : src/CMakeFiles/MyHttp.dir/requires

src/CMakeFiles/MyHttp.dir/clean:
	cd /root/HttpClient/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MyHttp.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/MyHttp.dir/clean

src/CMakeFiles/MyHttp.dir/depend:
	cd /root/HttpClient/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/HttpClient /root/HttpClient/src /root/HttpClient/build /root/HttpClient/build/src /root/HttpClient/build/src/CMakeFiles/MyHttp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/MyHttp.dir/depend

