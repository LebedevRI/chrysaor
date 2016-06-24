cmake_minimum_required(VERSION 3.5)

add_executable(Engine Engine.cpp main.cpp)

target_link_libraries(Engine libgtest)
target_link_libraries(Engine libchrysaor)

GTEST_ADD_TESTS(Engine "" AUTO)
