cmake_minimum_required(VERSION 3.5)

target_sources(libchrysaor
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/SemiMajorAxis.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpecificOrbitalEnergy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OrbitalEccentricity.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Apsis.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Periapsis.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Apoapsis.cpp"
)
