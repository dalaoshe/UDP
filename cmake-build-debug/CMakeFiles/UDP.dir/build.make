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
CMAKE_COMMAND = /home/dalaoshe/clion-2016.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/dalaoshe/clion-2016.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dalaoshe/network_demo/UDP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dalaoshe/network_demo/UDP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/UDP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UDP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UDP.dir/flags.make

CMakeFiles/UDP.dir/main.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/UDP.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/main.c.o   -c /home/dalaoshe/network_demo/UDP/main.c

CMakeFiles/UDP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/main.c > CMakeFiles/UDP.dir/main.c.i

CMakeFiles/UDP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/main.c -o CMakeFiles/UDP.dir/main.c.s

CMakeFiles/UDP.dir/main.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/main.c.o.requires

CMakeFiles/UDP.dir/main.c.o.provides: CMakeFiles/UDP.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/main.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/main.c.o.provides

CMakeFiles/UDP.dir/main.c.o.provides.build: CMakeFiles/UDP.dir/main.c.o


CMakeFiles/UDP.dir/recvfrom_flags.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/recvfrom_flags.c.o: ../recvfrom_flags.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/UDP.dir/recvfrom_flags.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/recvfrom_flags.c.o   -c /home/dalaoshe/network_demo/UDP/recvfrom_flags.c

CMakeFiles/UDP.dir/recvfrom_flags.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/recvfrom_flags.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/recvfrom_flags.c > CMakeFiles/UDP.dir/recvfrom_flags.c.i

CMakeFiles/UDP.dir/recvfrom_flags.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/recvfrom_flags.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/recvfrom_flags.c -o CMakeFiles/UDP.dir/recvfrom_flags.c.s

CMakeFiles/UDP.dir/recvfrom_flags.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/recvfrom_flags.c.o.requires

CMakeFiles/UDP.dir/recvfrom_flags.c.o.provides: CMakeFiles/UDP.dir/recvfrom_flags.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/recvfrom_flags.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/recvfrom_flags.c.o.provides

CMakeFiles/UDP.dir/recvfrom_flags.c.o.provides.build: CMakeFiles/UDP.dir/recvfrom_flags.c.o


CMakeFiles/UDP.dir/dg_send_recv.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/dg_send_recv.c.o: ../dg_send_recv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/UDP.dir/dg_send_recv.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/dg_send_recv.c.o   -c /home/dalaoshe/network_demo/UDP/dg_send_recv.c

CMakeFiles/UDP.dir/dg_send_recv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/dg_send_recv.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/dg_send_recv.c > CMakeFiles/UDP.dir/dg_send_recv.c.i

CMakeFiles/UDP.dir/dg_send_recv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/dg_send_recv.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/dg_send_recv.c -o CMakeFiles/UDP.dir/dg_send_recv.c.s

CMakeFiles/UDP.dir/dg_send_recv.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/dg_send_recv.c.o.requires

CMakeFiles/UDP.dir/dg_send_recv.c.o.provides: CMakeFiles/UDP.dir/dg_send_recv.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/dg_send_recv.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/dg_send_recv.c.o.provides

CMakeFiles/UDP.dir/dg_send_recv.c.o.provides.build: CMakeFiles/UDP.dir/dg_send_recv.c.o


CMakeFiles/UDP.dir/rtt.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/rtt.c.o: ../rtt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/UDP.dir/rtt.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/rtt.c.o   -c /home/dalaoshe/network_demo/UDP/rtt.c

CMakeFiles/UDP.dir/rtt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/rtt.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/rtt.c > CMakeFiles/UDP.dir/rtt.c.i

CMakeFiles/UDP.dir/rtt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/rtt.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/rtt.c -o CMakeFiles/UDP.dir/rtt.c.s

CMakeFiles/UDP.dir/rtt.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/rtt.c.o.requires

CMakeFiles/UDP.dir/rtt.c.o.provides: CMakeFiles/UDP.dir/rtt.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/rtt.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/rtt.c.o.provides

CMakeFiles/UDP.dir/rtt.c.o.provides.build: CMakeFiles/UDP.dir/rtt.c.o


CMakeFiles/UDP.dir/do_client.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/do_client.c.o: ../do_client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/UDP.dir/do_client.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/do_client.c.o   -c /home/dalaoshe/network_demo/UDP/do_client.c

CMakeFiles/UDP.dir/do_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/do_client.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/do_client.c > CMakeFiles/UDP.dir/do_client.c.i

CMakeFiles/UDP.dir/do_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/do_client.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/do_client.c -o CMakeFiles/UDP.dir/do_client.c.s

CMakeFiles/UDP.dir/do_client.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/do_client.c.o.requires

CMakeFiles/UDP.dir/do_client.c.o.provides: CMakeFiles/UDP.dir/do_client.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/do_client.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/do_client.c.o.provides

CMakeFiles/UDP.dir/do_client.c.o.provides.build: CMakeFiles/UDP.dir/do_client.c.o


CMakeFiles/UDP.dir/error_check.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/error_check.c.o: ../error_check.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/UDP.dir/error_check.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/error_check.c.o   -c /home/dalaoshe/network_demo/UDP/error_check.c

CMakeFiles/UDP.dir/error_check.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/error_check.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/error_check.c > CMakeFiles/UDP.dir/error_check.c.i

CMakeFiles/UDP.dir/error_check.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/error_check.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/error_check.c -o CMakeFiles/UDP.dir/error_check.c.s

CMakeFiles/UDP.dir/error_check.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/error_check.c.o.requires

CMakeFiles/UDP.dir/error_check.c.o.provides: CMakeFiles/UDP.dir/error_check.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/error_check.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/error_check.c.o.provides

CMakeFiles/UDP.dir/error_check.c.o.provides.build: CMakeFiles/UDP.dir/error_check.c.o


CMakeFiles/UDP.dir/do_server.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/do_server.c.o: ../do_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/UDP.dir/do_server.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/do_server.c.o   -c /home/dalaoshe/network_demo/UDP/do_server.c

CMakeFiles/UDP.dir/do_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/do_server.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/do_server.c > CMakeFiles/UDP.dir/do_server.c.i

CMakeFiles/UDP.dir/do_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/do_server.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/do_server.c -o CMakeFiles/UDP.dir/do_server.c.s

CMakeFiles/UDP.dir/do_server.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/do_server.c.o.requires

CMakeFiles/UDP.dir/do_server.c.o.provides: CMakeFiles/UDP.dir/do_server.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/do_server.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/do_server.c.o.provides

CMakeFiles/UDP.dir/do_server.c.o.provides.build: CMakeFiles/UDP.dir/do_server.c.o


CMakeFiles/UDP.dir/token_bucket.c.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/token_bucket.c.o: ../token_bucket.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/UDP.dir/token_bucket.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UDP.dir/token_bucket.c.o   -c /home/dalaoshe/network_demo/UDP/token_bucket.c

CMakeFiles/UDP.dir/token_bucket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UDP.dir/token_bucket.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dalaoshe/network_demo/UDP/token_bucket.c > CMakeFiles/UDP.dir/token_bucket.c.i

CMakeFiles/UDP.dir/token_bucket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UDP.dir/token_bucket.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dalaoshe/network_demo/UDP/token_bucket.c -o CMakeFiles/UDP.dir/token_bucket.c.s

CMakeFiles/UDP.dir/token_bucket.c.o.requires:

.PHONY : CMakeFiles/UDP.dir/token_bucket.c.o.requires

CMakeFiles/UDP.dir/token_bucket.c.o.provides: CMakeFiles/UDP.dir/token_bucket.c.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/token_bucket.c.o.provides.build
.PHONY : CMakeFiles/UDP.dir/token_bucket.c.o.provides

CMakeFiles/UDP.dir/token_bucket.c.o.provides.build: CMakeFiles/UDP.dir/token_bucket.c.o


CMakeFiles/UDP.dir/token_bucken_map.cpp.o: CMakeFiles/UDP.dir/flags.make
CMakeFiles/UDP.dir/token_bucken_map.cpp.o: ../token_bucken_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/UDP.dir/token_bucken_map.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UDP.dir/token_bucken_map.cpp.o -c /home/dalaoshe/network_demo/UDP/token_bucken_map.cpp

CMakeFiles/UDP.dir/token_bucken_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UDP.dir/token_bucken_map.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dalaoshe/network_demo/UDP/token_bucken_map.cpp > CMakeFiles/UDP.dir/token_bucken_map.cpp.i

CMakeFiles/UDP.dir/token_bucken_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UDP.dir/token_bucken_map.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dalaoshe/network_demo/UDP/token_bucken_map.cpp -o CMakeFiles/UDP.dir/token_bucken_map.cpp.s

CMakeFiles/UDP.dir/token_bucken_map.cpp.o.requires:

.PHONY : CMakeFiles/UDP.dir/token_bucken_map.cpp.o.requires

CMakeFiles/UDP.dir/token_bucken_map.cpp.o.provides: CMakeFiles/UDP.dir/token_bucken_map.cpp.o.requires
	$(MAKE) -f CMakeFiles/UDP.dir/build.make CMakeFiles/UDP.dir/token_bucken_map.cpp.o.provides.build
.PHONY : CMakeFiles/UDP.dir/token_bucken_map.cpp.o.provides

CMakeFiles/UDP.dir/token_bucken_map.cpp.o.provides.build: CMakeFiles/UDP.dir/token_bucken_map.cpp.o


# Object files for target UDP
UDP_OBJECTS = \
"CMakeFiles/UDP.dir/main.c.o" \
"CMakeFiles/UDP.dir/recvfrom_flags.c.o" \
"CMakeFiles/UDP.dir/dg_send_recv.c.o" \
"CMakeFiles/UDP.dir/rtt.c.o" \
"CMakeFiles/UDP.dir/do_client.c.o" \
"CMakeFiles/UDP.dir/error_check.c.o" \
"CMakeFiles/UDP.dir/do_server.c.o" \
"CMakeFiles/UDP.dir/token_bucket.c.o" \
"CMakeFiles/UDP.dir/token_bucken_map.cpp.o"

# External object files for target UDP
UDP_EXTERNAL_OBJECTS =

UDP: CMakeFiles/UDP.dir/main.c.o
UDP: CMakeFiles/UDP.dir/recvfrom_flags.c.o
UDP: CMakeFiles/UDP.dir/dg_send_recv.c.o
UDP: CMakeFiles/UDP.dir/rtt.c.o
UDP: CMakeFiles/UDP.dir/do_client.c.o
UDP: CMakeFiles/UDP.dir/error_check.c.o
UDP: CMakeFiles/UDP.dir/do_server.c.o
UDP: CMakeFiles/UDP.dir/token_bucket.c.o
UDP: CMakeFiles/UDP.dir/token_bucken_map.cpp.o
UDP: CMakeFiles/UDP.dir/build.make
UDP: CMakeFiles/UDP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable UDP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UDP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UDP.dir/build: UDP

.PHONY : CMakeFiles/UDP.dir/build

CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/main.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/recvfrom_flags.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/dg_send_recv.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/rtt.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/do_client.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/error_check.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/do_server.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/token_bucket.c.o.requires
CMakeFiles/UDP.dir/requires: CMakeFiles/UDP.dir/token_bucken_map.cpp.o.requires

.PHONY : CMakeFiles/UDP.dir/requires

CMakeFiles/UDP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UDP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UDP.dir/clean

CMakeFiles/UDP.dir/depend:
	cd /home/dalaoshe/network_demo/UDP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dalaoshe/network_demo/UDP /home/dalaoshe/network_demo/UDP /home/dalaoshe/network_demo/UDP/cmake-build-debug /home/dalaoshe/network_demo/UDP/cmake-build-debug /home/dalaoshe/network_demo/UDP/cmake-build-debug/CMakeFiles/UDP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UDP.dir/depend

