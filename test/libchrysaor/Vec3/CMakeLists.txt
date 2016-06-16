cmake_minimum_required(VERSION 3.5)

add_executable(Vec3 Vec3.cpp Vec3ScalarOps.cpp Vec3VectorOps.cpp Vec3Norm.cpp Vec3Dot.cpp Vec3Cross.cpp main.cpp)

target_link_libraries(Vec3 libgtest)
target_link_libraries(Vec3 libchrysaor)

GTEST_ADD_TESTS(Vec3 "" AUTO)
