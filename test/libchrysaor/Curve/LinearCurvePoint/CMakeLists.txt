cmake_minimum_required(VERSION 3.5)

add_executable(LinearCurvePoint LinearCurvePoint.cpp main.cpp)

target_link_libraries(LinearCurvePoint libgtest)
target_link_libraries(LinearCurvePoint libchrysaor)

GTEST_ADD_TESTS(LinearCurvePoint "" AUTO)
