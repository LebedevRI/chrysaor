cmake_minimum_required(VERSION 3.5)

add_executable(Stage Stage.cpp main.cpp)

target_link_libraries(Stage libgtest)

GTEST_ADD_TESTS(Stage "" AUTO)
