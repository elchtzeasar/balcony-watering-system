cmake_minimum_required (VERSION 2.8.11)
project (BalconyWateringSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory (platform)
add_subdirectory (configuration)
add_subdirectory (hardware)
add_subdirectory (logic)
add_subdirectory (ui)

add_subdirectory (main)

