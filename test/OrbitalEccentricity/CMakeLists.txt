cmake_minimum_required(VERSION 3.5)

add_executable(OrbitalEccentricity OrbitalEccentricity.cpp CircularOrbit.cpp EllipticalOrbit.cpp main.cpp)

target_link_libraries(OrbitalEccentricity libgtest)
target_link_libraries(OrbitalEccentricity libchrysaor)

add_test(OrbitalEccentricity OrbitalEccentricity)
