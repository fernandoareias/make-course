cmake_minimum_required(VERSION 3.16)
project(BitVault LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare (
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare (
    zlib
    URL https://github.com/madler/zlib/releases/download/v1.4/zlib14.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(zlib)

include(cmake/AddApp.cmake)
include(cmake/AddLib.cmake)
include(cmake/AddTest.cmake)

include_directories(src)

add_subdirectory(src)
add_subdirectory(app)
enable_testing()
add_subdirectory(tests)