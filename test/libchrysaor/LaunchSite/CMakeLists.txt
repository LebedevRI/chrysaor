cmake_minimum_required(VERSION 3.5)

add_executable(LaunchSite LaunchSite.cpp main.cpp)

target_link_libraries(LaunchSite libgtest)
target_link_libraries(LaunchSite libchrysaor)

GTEST_ADD_TESTS(LaunchSite "" AUTO)
