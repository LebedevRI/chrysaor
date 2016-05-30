cmake_minimum_required(VERSION 3.5)

add_executable(CubicCurvePoint CubicCurvePoint.cpp main.cpp)

target_link_libraries(CubicCurvePoint libgtest)

add_test(CubicCurvePoint CubicCurvePoint)
