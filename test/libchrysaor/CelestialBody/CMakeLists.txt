cmake_minimum_required(VERSION 3.5)

add_executable(CelestialBody CelestialBody.cpp main.cpp)

target_link_libraries(CelestialBody libgtest)
target_link_libraries(CelestialBody libchrysaor)

GTEST_ADD_TESTS(CelestialBody "" AUTO)
