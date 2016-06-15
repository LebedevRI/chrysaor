cmake_minimum_required(VERSION 3.5)

add_executable(SpecificOrbitalEnergy SpecificOrbitalEnergy.cpp EllipticalOrbit.cpp main.cpp)

target_link_libraries(SpecificOrbitalEnergy libgtest)
target_link_libraries(SpecificOrbitalEnergy libchrysaor)

GTEST_ADD_TESTS(SpecificOrbitalEnergy "" AUTO)
