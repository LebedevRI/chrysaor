cmake_minimum_required(VERSION 3.5)

add_executable(CubicCurve CubicCurve.cpp main.cpp)

target_link_libraries(CubicCurve libgtest)

add_test(CubicCurve CubicCurve)
