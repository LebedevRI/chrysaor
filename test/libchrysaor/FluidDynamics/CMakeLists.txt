cmake_minimum_required(VERSION 3.5)

add_executable(FluidDynamics FluidDynamics.cpp main.cpp)

target_link_libraries(FluidDynamics libgtest)
target_link_libraries(FluidDynamics libchrysaor)

GTEST_ADD_TESTS(FluidDynamics "" AUTO)
