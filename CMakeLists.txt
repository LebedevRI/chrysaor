cmake_minimum_required(VERSION 3.5)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

If(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not permitted.\n"
          "Make a separate folder for building:\n"
          "$ mkdir build; cd build; cmake ..\n"
          "Before that, remove the files already created:\n"
          "$ rm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

project(chrysaor CXX)

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules")

# Add a sensible build type default and warning because empty means no optimization and no debug info.
if(NOT CMAKE_BUILD_TYPE)
  message("WARNING: CMAKE_BUILD_TYPE is not defined!\n"
          "\tDefaulting to CMAKE_BUILD_TYPE=RelWithDebInfo.")
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

include(CTest)

option(BUILD_DOC "Build the documentation" ON)
option(USE_IWYU "Run iwyu tool when compiling sources" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

ADD_DEFINITIONS(-Wall)
ADD_DEFINITIONS(-Werror)

#MESSAGE(FATAL_ERROR ${CMAKE_CXX_COMPILER_ID})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  ADD_DEFINITIONS(-Wextra)
  ADD_DEFINITIONS(-Weverything)

  ADD_DEFINITIONS(-Wno-c++98-compat)
  ADD_DEFINITIONS(-Wno-global-constructors)

  ADD_DEFINITIONS(-Wno-error=missing-prototypes)
  ADD_DEFINITIONS(-Wno-error=missing-variable-declarations)

  ADD_DEFINITIONS(-Wno-error=unused-private-field)
  ADD_DEFINITIONS(-Wno-error=float-equal)
  ADD_DEFINITIONS(-Wno-error=weak-vtables)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  ADD_DEFINITIONS(-Wextra)
endif()

include(CpuMarch)

find_package(Threads REQUIRED)

if(USE_IWYU)
  find_program(iwyu_path NAMES include-what-you-use iwyu)
  if(NOT iwyu_path)
    message(FATAL_ERROR "Could not find the program include-what-you-use")
  else(NOT iwyu_path)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${iwyu_path}")
  endif()
endif()

if(BUILD_TESTING)
# at least in debian, they are the package only installs their source code,
# so if one wants to use them, he needs to compile them in-tree
  include(GTest)
  # include(GMock)

  enable_testing()
endif(BUILD_TESTING)

if(BUILD_DOC)
  find_package(Doxygen REQUIRED)
  FIND_PROGRAM(DOT_PATH dot)

  IF(NOT DOT_PATH)
    MESSAGE(FATAL_ERROR "dot not found! Aborting...")
  ENDIF(NOT DOT_PATH)

  configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ALL
                    ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
                    DEPENDS ${CMAKE_BINARY_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM
                    SOURCES ${CMAKE_BINARY_DIR}/Doxyfile)
endif(BUILD_DOC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage" AND CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  setup_target_for_coverage(coverage make coverage test)
endif(CMAKE_BUILD_TYPE STREQUAL "Coverage" AND CMAKE_COMPILER_IS_GNUCXX)
