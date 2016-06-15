cmake_minimum_required(VERSION 3.5)

add_executable(LaunchSite LaunchSite.cpp main.cpp)

target_link_libraries(LaunchSite libgtest)

GTEST_ADD_TESTS(LaunchSite "" AUTO)
