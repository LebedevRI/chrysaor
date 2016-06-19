cmake_minimum_required(VERSION 3.5)

add_executable(LinearCurve LinearCurve.cpp main.cpp)

target_link_libraries(LinearCurve libgtest)
target_link_libraries(LinearCurve libchrysaor)

GTEST_ADD_TESTS(LinearCurve "" AUTO)
