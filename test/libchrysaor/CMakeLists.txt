cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(CelestialBody)

add_subdirectory(SpecificRelativeAngularMomentum)

add_subdirectory(OrbitalElements)

add_subdirectory(Vec3)

add_subdirectory(LaunchSite)
add_subdirectory(Stage)
add_subdirectory(Curve)
add_subdirectory(IdealGas)
add_subdirectory(FluidDynamics)
