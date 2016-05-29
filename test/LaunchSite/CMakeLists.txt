cmake_minimum_required(VERSION 3.5)

add_executable(LaunchSite LaunchSite.cpp main.cpp)

target_link_libraries(LaunchSite libgtest)

add_test(LaunchSite LaunchSite)
