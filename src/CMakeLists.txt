cmake_minimum_required(VERSION 3.5)

add_library(libchrysaor SHARED
  SemiMajorAxis.cpp
  SpecificOrbitalEnergy.cpp
  SpecificRelativeAngularMomentum.cpp
  OrbitalEccentricity.cpp
  Apsis.cpp
  Periapsis.cpp
  Apoapsis.cpp
)

set_target_properties(libchrysaor PROPERTIES OUTPUT_NAME chrysaor)

add_executable(chrysaor main.cpp)
