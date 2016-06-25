cmake_minimum_required(VERSION 3.5)

project(libchrysaor LANGUAGES CXX)

add_library(libchrysaor SHARED
  SpecificRelativeAngularMomentum.cpp

  CelestialBody.cpp

  Vec3.cpp
  LaunchSite.cpp
  IdealGas.cpp
  FluidDynamics.cpp
  Atmosphere.cpp
)

add_subdirectory(OrbitalElements)
add_subdirectory(Curve)
add_subdirectory(Vehicle)

target_include_directories(libchrysaor PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(libchrysaor PROPERTIES OUTPUT_NAME chrysaor)
