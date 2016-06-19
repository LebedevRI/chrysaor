cmake_minimum_required(VERSION 3.5)

add_executable(CubicCurve CubicCurve.cpp main.cpp)

target_link_libraries(CubicCurve libgtest)
target_link_libraries(CubicCurve libchrysaor)

GTEST_ADD_TESTS(CubicCurve "" AUTO)
