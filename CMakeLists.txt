cmake_minimum_required(VERSION 3.16)
project(BitVault LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

include(cmake/AddApp.cmake)
include(cmake/AddLib.cmake)
include(cmake/AddTest.cmake)

include_directories(src)

add_subdirectory(src)
add_subdirectory(app)
enable_testing()
add_subdirectory(tests)