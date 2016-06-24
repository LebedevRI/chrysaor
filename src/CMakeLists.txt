cmake_minimum_required(VERSION 3.5)

ADD_DEFINITIONS(-Wframe-larger-than=256)

add_subdirectory(libchrysaor)

add_executable(chrysaor main.cpp)
