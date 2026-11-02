cmake_minimum_required(VERSION 3.20.0)


list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

zephyr_include_directories(include)

add_subdirectory(drivers/our_driver)
target_sources(app PRIVATE src/main.cpp)