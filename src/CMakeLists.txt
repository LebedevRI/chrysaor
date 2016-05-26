cmake_minimum_required(VERSION 3.5)

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

add_executable(chrysaor main.cpp)
