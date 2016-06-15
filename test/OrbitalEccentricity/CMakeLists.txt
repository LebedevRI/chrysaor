cmake_minimum_required(VERSION 3.5)

add_executable(OrbitalEccentricity OrbitalEccentricity.cpp EllipticalOrbit.cpp main.cpp)

target_link_libraries(OrbitalEccentricity libgtest)
target_link_libraries(OrbitalEccentricity libchrysaor)

GTEST_ADD_TESTS(OrbitalEccentricity "" AUTO)
