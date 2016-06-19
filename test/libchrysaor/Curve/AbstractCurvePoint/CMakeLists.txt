cmake_minimum_required(VERSION 3.5)

add_executable(AbstractCurvePoint AbstractCurvePoint.cpp main.cpp)

target_link_libraries(AbstractCurvePoint libgtest)
target_link_libraries(AbstractCurvePoint libchrysaor)

GTEST_ADD_TESTS(AbstractCurvePoint "" AUTO)
