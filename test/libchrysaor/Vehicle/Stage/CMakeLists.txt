cmake_minimum_required(VERSION 3.5)

add_executable(Stage Stage.cpp main.cpp)

target_link_libraries(Stage libgtest)
target_link_libraries(Stage libchrysaor)

GTEST_ADD_TESTS(Stage "" AUTO)
