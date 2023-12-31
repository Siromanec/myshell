cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
#  It is used as your project's main executable name. 
set(PROJECT_NAME myshell)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 20)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too many problems for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS OFF)

#! Always use PVS Studio while developing.
set(ENABLE_PVS_STUDIO OFF)

#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of the Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan).
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
#  Info: https://clang.llvm.org/docs/ThreadSanitizer.html
set(ENABLE_TSan OFF)
#! MemorySanitizer -- detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)
#include(myshell/Cmake)
include_directories(mycat)
#TODO
##########################################################
# Project files, packages, libraries and so on
##########################################################

#! Project main executable source compilation

set(CLASSDIRS options_parser myshell command internal-commands prompt-putter history-saver)
add_executable(${PROJECT_NAME} main.cpp
				options_parser/options_parser.cpp options_parser/options_parser.h
		myshell/AbstractRunner.cpp myshell/AbstractRunner.hpp
		command/Command.cpp command/Command.hpp command/InternalCommand.cpp
		command/InternalCommand.hpp command/ExternalCommand.cpp command/ExternalCommand.hpp command/ScriptCommand.cpp command/ScriptCommand.hpp
		myshell/MyShell.cpp myshell/MyShell.hpp myshell/ScriptRunner.cpp myshell/ScriptRunner.hpp
		internal-commands/internal_commands-POSIX.cpp internal-commands/internal_commands-POSIX.hpp
		prompt-putter/PromptPutter.hpp prompt-putter/PromptPutter.cpp
		history-saver/HistorySaver.hpp history-saver/HistorySaver.cpp)

#! Put path to your project headers
if (DEBUG)
	add_definitions(-DDEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSDIRS})

#! Add external packages
# options_parser requires boost::program_options library
find_package(Boost 1.71.0 COMPONENTS program_options system filesystem REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Boost::program_options Boost::system Boost::filesystem)
target_link_libraries(${PROJECT_NAME} readline)


##########################################################
# Fixed CMakeLists.txt part
##########################################################

INSTALL(PROGRAMS
		$<TARGET_FILE:${PROJECT_NAME}> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
		DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME})

# Include CMake setup
include(cmake/main-config.cmake)
