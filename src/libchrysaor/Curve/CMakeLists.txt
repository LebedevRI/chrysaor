cmake_minimum_required(VERSION 3.5)

target_sources(libchrysaor
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/CubicCurvePoint.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/CubicCurve.cpp"
)
