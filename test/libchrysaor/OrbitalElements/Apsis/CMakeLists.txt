cmake_minimum_required(VERSION 3.5)

add_executable(Apsis EllipticalOrbit.cpp main.cpp)

target_link_libraries(Apsis libgtest)
target_link_libraries(Apsis libchrysaor)

GTEST_ADD_TESTS(Apsis "" AUTO)
