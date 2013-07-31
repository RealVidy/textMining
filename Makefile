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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/presta/Project/textMining

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/presta/Project/textMining

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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/presta/Project/textMining/CMakeFiles /home/presta/Project/textMining/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/presta/Project/textMining/CMakeFiles 0
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
# Target rules for targets named TextMiningApp

# Build rule for target.
TextMiningApp: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TextMiningApp
.PHONY : TextMiningApp

# fast build rule for target.
TextMiningApp/fast:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/build
.PHONY : TextMiningApp/fast

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
# Target rules for targets named doc

# Build rule for target.
doc: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 doc
.PHONY : doc

# fast build rule for target.
doc/fast:
	$(MAKE) -f CMakeFiles/doc.dir/build.make CMakeFiles/doc.dir/build
.PHONY : doc/fast

src/compilator/compilator.o: src/compilator/compilator.cpp.o
.PHONY : src/compilator/compilator.o

# target to build an object file
src/compilator/compilator.cpp.o:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/compilator/compilator.cpp.o
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/compilator/compilator.cpp.o
.PHONY : src/compilator/compilator.cpp.o

src/compilator/compilator.i: src/compilator/compilator.cpp.i
.PHONY : src/compilator/compilator.i

# target to preprocess a source file
src/compilator/compilator.cpp.i:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/compilator/compilator.cpp.i
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/compilator/compilator.cpp.i
.PHONY : src/compilator/compilator.cpp.i

src/compilator/compilator.s: src/compilator/compilator.cpp.s
.PHONY : src/compilator/compilator.s

# target to generate assembly for a file
src/compilator/compilator.cpp.s:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/compilator/compilator.cpp.s
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/compilator/compilator.cpp.s
.PHONY : src/compilator/compilator.cpp.s

src/compilator/main.o: src/compilator/main.cpp.o
.PHONY : src/compilator/main.o

# target to build an object file
src/compilator/main.cpp.o:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/compilator/main.cpp.o
.PHONY : src/compilator/main.cpp.o

src/compilator/main.i: src/compilator/main.cpp.i
.PHONY : src/compilator/main.i

# target to preprocess a source file
src/compilator/main.cpp.i:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/compilator/main.cpp.i
.PHONY : src/compilator/main.cpp.i

src/compilator/main.s: src/compilator/main.cpp.s
.PHONY : src/compilator/main.s

# target to generate assembly for a file
src/compilator/main.cpp.s:
	$(MAKE) -f CMakeFiles/TextMiningCompiler.dir/build.make CMakeFiles/TextMiningCompiler.dir/src/compilator/main.cpp.s
.PHONY : src/compilator/main.cpp.s

src/interpreter/interpreter.o: src/interpreter/interpreter.cpp.o
.PHONY : src/interpreter/interpreter.o

# target to build an object file
src/interpreter/interpreter.cpp.o:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/interpreter/interpreter.cpp.o
.PHONY : src/interpreter/interpreter.cpp.o

src/interpreter/interpreter.i: src/interpreter/interpreter.cpp.i
.PHONY : src/interpreter/interpreter.i

# target to preprocess a source file
src/interpreter/interpreter.cpp.i:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/interpreter/interpreter.cpp.i
.PHONY : src/interpreter/interpreter.cpp.i

src/interpreter/interpreter.s: src/interpreter/interpreter.cpp.s
.PHONY : src/interpreter/interpreter.s

# target to generate assembly for a file
src/interpreter/interpreter.cpp.s:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/interpreter/interpreter.cpp.s
.PHONY : src/interpreter/interpreter.cpp.s

src/interpreter/main.o: src/interpreter/main.cpp.o
.PHONY : src/interpreter/main.o

# target to build an object file
src/interpreter/main.cpp.o:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/interpreter/main.cpp.o
.PHONY : src/interpreter/main.cpp.o

src/interpreter/main.i: src/interpreter/main.cpp.i
.PHONY : src/interpreter/main.i

# target to preprocess a source file
src/interpreter/main.cpp.i:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/interpreter/main.cpp.i
.PHONY : src/interpreter/main.cpp.i

src/interpreter/main.s: src/interpreter/main.cpp.s
.PHONY : src/interpreter/main.s

# target to generate assembly for a file
src/interpreter/main.cpp.s:
	$(MAKE) -f CMakeFiles/TextMiningApp.dir/build.make CMakeFiles/TextMiningApp.dir/src/interpreter/main.cpp.s
.PHONY : src/interpreter/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... TextMiningApp"
	@echo "... TextMiningCompiler"
	@echo "... distclean"
	@echo "... doc"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src/compilator/compilator.o"
	@echo "... src/compilator/compilator.i"
	@echo "... src/compilator/compilator.s"
	@echo "... src/compilator/main.o"
	@echo "... src/compilator/main.i"
	@echo "... src/compilator/main.s"
	@echo "... src/interpreter/interpreter.o"
	@echo "... src/interpreter/interpreter.i"
	@echo "... src/interpreter/interpreter.s"
	@echo "... src/interpreter/main.o"
	@echo "... src/interpreter/main.i"
	@echo "... src/interpreter/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

