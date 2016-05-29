cmake_minimum_required(VERSION 3.5)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

If(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

project(chrysaor CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include(CheckCXXCompilerFlag)

ADD_DEFINITIONS(-Wall)
ADD_DEFINITIONS(-Werror)

MESSAGE("-- Checking for -march=native support")
CHECK_CXX_COMPILER_FLAG("-march=native" MARCHNATIVE)
if(MARCHNATIVE)
  set(MARCH "-march=native")
else()
  MESSAGE("-- Checking for -mtune=native support")
  CHECK_CXX_COMPILER_FLAG("-mtune=native" MTUNENATIVE)
  if (MTUNENATIVE)
    set(MARCH "-mtune=native")
  else()
    set(MARCH "-mtune=generic")
  endif()
endif()

ADD_DEFINITIONS(${MARCH})

find_package(Threads REQUIRED)

find_program(iwyu_path NAMES include-what-you-use iwyu)
if(NOT iwyu_path)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
else(NOT iwyu_path)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${iwyu_path}")
endif()

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(test)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage" AND CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  setup_target_for_coverage(coverage make coverage test)
endif(CMAKE_BUILD_TYPE STREQUAL "Coverage" AND CMAKE_COMPILER_IS_GNUCXX)
