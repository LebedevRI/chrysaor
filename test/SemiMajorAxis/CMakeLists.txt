cmake_minimum_required(VERSION 3.5)

add_executable(SemiMajorAxis SemiMajorAxis.cpp CircularOrbit.cpp EllipticalOrbit.cpp main.cpp)

target_link_libraries(SemiMajorAxis libgtest)

add_test(SemiMajorAxis SemiMajorAxis)
