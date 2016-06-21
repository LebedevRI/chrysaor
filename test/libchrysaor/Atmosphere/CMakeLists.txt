cmake_minimum_required(VERSION 3.5)

add_executable(Atmosphere Atmosphere.cpp main.cpp)

target_link_libraries(Atmosphere libgtest)
target_link_libraries(Atmosphere libchrysaor)

GTEST_ADD_TESTS(Atmosphere "" AUTO)
