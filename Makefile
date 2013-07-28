# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yussak/textMining

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yussak/textMining

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/yussak/textMining/CMakeFiles /home/yussak/textMining/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/yussak/textMining/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named TextMiningCompiler

# Build rule for target.
TextMiningCompiler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TextMiningCompiler
.PHONY : TextMiningCompiler

# fast build rule for target.
TextMiningCompiler/fast:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/build
.PHONY : TextMiningCompiler/fast

#=============================================================================
# Target rules for targets named clean

# Build rule for target.
clean: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# fast build rule for target.
clean/fast:
	$(MAKE) -f CMakeFiles/clean.dir/build.make CMakeFiles/clean.dir/build
.PHONY : clean/fast

#=============================================================================
# Target rules for targets named distclean

# Build rule for target.
distclean: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 distclean
.PHONY : distclean

# fast build rule for target.
distclean/fast:
	$(MAKE) -f CMakeFiles/distclean.dir/build.make CMakeFiles/distclean.dir/build
.PHONY : distclean/fast

#=============================================================================
# Target rules for targets named interpreter

# Build rule for target.
interpreter: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 interpreter
.PHONY : interpreter

# fast build rule for target.
interpreter/fast:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/build
.PHONY : interpreter/fast

src/interpreter/interpreter.o: src/interpreter/interpreter.cpp.o
.PHONY : src/interpreter/interpreter.o

# target to build an object file
src/interpreter/interpreter.cpp.o:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter/interpreter.cpp.o
.PHONY : src/interpreter/interpreter.cpp.o

src/interpreter/interpreter.i: src/interpreter/interpreter.cpp.i
.PHONY : src/interpreter/interpreter.i

# target to preprocess a source file
src/interpreter/interpreter.cpp.i:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter/interpreter.cpp.i
.PHONY : src/interpreter/interpreter.cpp.i

src/interpreter/interpreter.s: src/interpreter/interpreter.cpp.s
.PHONY : src/interpreter/interpreter.s

# target to generate assembly for a file
src/interpreter/interpreter.cpp.s:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter/interpreter.cpp.s
.PHONY : src/interpreter/interpreter.cpp.s

src/interpreter/main.o: src/interpreter/main.cpp.o
.PHONY : src/interpreter/main.o

# target to build an object file
src/interpreter/main.cpp.o:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter/main.cpp.o
.PHONY : src/interpreter/main.cpp.o

src/interpreter/main.i: src/interpreter/main.cpp.i
.PHONY : src/interpreter/main.i

# target to preprocess a source file
src/interpreter/main.cpp.i:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter/main.cpp.i
.PHONY : src/interpreter/main.cpp.i

src/interpreter/main.s: src/interpreter/main.cpp.s
.PHONY : src/interpreter/main.s

# target to generate assembly for a file
src/interpreter/main.cpp.s:
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter/main.cpp.s
.PHONY : src/interpreter/main.cpp.s

src/patriciaTrie/main.o: src/patriciaTrie/main.cpp.o
.PHONY : src/patriciaTrie/main.o

# target to build an object file
src/patriciaTrie/main.cpp.o:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/patriciaTrie/main.cpp.o
.PHONY : src/patriciaTrie/main.cpp.o

src/patriciaTrie/main.i: src/patriciaTrie/main.cpp.i
.PHONY : src/patriciaTrie/main.i

# target to preprocess a source file
src/patriciaTrie/main.cpp.i:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/patriciaTrie/main.cpp.i
.PHONY : src/patriciaTrie/main.cpp.i

src/patriciaTrie/main.s: src/patriciaTrie/main.cpp.s
.PHONY : src/patriciaTrie/main.s

# target to generate assembly for a file
src/patriciaTrie/main.cpp.s:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/patriciaTrie/main.cpp.s
.PHONY : src/patriciaTrie/main.cpp.s

src/patriciaTrie/patriciaTrie.o: src/patriciaTrie/patriciaTrie.cpp.o
.PHONY : src/patriciaTrie/patriciaTrie.o

# target to build an object file
src/patriciaTrie/patriciaTrie.cpp.o:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/patriciaTrie/patriciaTrie.cpp.o
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/patriciaTrie/patriciaTrie.cpp.o
.PHONY : src/patriciaTrie/patriciaTrie.cpp.o

src/patriciaTrie/patriciaTrie.i: src/patriciaTrie/patriciaTrie.cpp.i
.PHONY : src/patriciaTrie/patriciaTrie.i

# target to preprocess a source file
src/patriciaTrie/patriciaTrie.cpp.i:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/patriciaTrie/patriciaTrie.cpp.i
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/patriciaTrie/patriciaTrie.cpp.i
.PHONY : src/patriciaTrie/patriciaTrie.cpp.i

src/patriciaTrie/patriciaTrie.s: src/patriciaTrie/patriciaTrie.cpp.s
.PHONY : src/patriciaTrie/patriciaTrie.s

# target to generate assembly for a file
src/patriciaTrie/patriciaTrie.cpp.s:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/patriciaTrie/patriciaTrie.cpp.s
	$(MAKE) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/patriciaTrie/patriciaTrie.cpp.s
.PHONY : src/patriciaTrie/patriciaTrie.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... TextMiningCompiler"
	@echo "... clean"
	@echo "... distclean"
	@echo "... edit_cache"
	@echo "... interpreter"
	@echo "... rebuild_cache"
	@echo "... src/interpreter/interpreter.o"
	@echo "... src/interpreter/interpreter.i"
	@echo "... src/interpreter/interpreter.s"
	@echo "... src/interpreter/main.o"
	@echo "... src/interpreter/main.i"
	@echo "... src/interpreter/main.s"
	@echo "... src/patriciaTrie/main.o"
	@echo "... src/patriciaTrie/main.i"
	@echo "... src/patriciaTrie/main.s"
	@echo "... src/patriciaTrie/patriciaTrie.o"
	@echo "... src/patriciaTrie/patriciaTrie.i"
	@echo "... src/patriciaTrie/patriciaTrie.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

