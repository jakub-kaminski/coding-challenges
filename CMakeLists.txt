cmake_minimum_required(VERSION 3.23)
project(CPP-SOLUTIONS LANGUAGES CXX)

enable_testing()

#Include macros
file(GLOB macros "Macros/*.cmake")
FOREACH(macro ${macros})
  include("${macro}")
ENDFOREACH()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(FetchContent)
#FetchContent_Declare(
#  googletest
#  GIT_REPOSITORY https://github.com/google/googletest.git
#  GIT_TAG release-1.12.1
#)

# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.0)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)

SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR})
list(REMOVE_ITEM SUBDIRS ".idea" "build" ".git" "cmake-build-release" "cmake-build-debug" "Macros" "Unused")

FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()
