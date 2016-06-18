cmake_minimum_required(VERSION 3.5)

add_executable(IdealGas IdealGas.cpp main.cpp)

target_link_libraries(IdealGas libgtest)
target_link_libraries(IdealGas libchrysaor)

GTEST_ADD_TESTS(IdealGas "" AUTO)
