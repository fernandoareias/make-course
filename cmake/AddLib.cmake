macro(add_lib_custom name type)

#INTERFACE (Header only lib) | STATIC (Lib Static) | SHARED (Dynamic lib) 

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE LIB_SOURCES
    "${SOURCE_DIR}/*.c"
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.h"
    "${SOURCE_DIR}/*.hpp"
)

add_library(${name} ${type} ${LIB_SOURCES})


if (${type} STREQUAL "INTERFACE")   
    target_include_directories(${name} INTERFACE ${SOURCE_DIR} ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
else()
    target_include_directories(${name} PUBLIC ${SOURCE_DIR} ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
endif()

if(NOT "${ARGN}" STREQUAL "")
    target_link_libraries(${name} PUBLIC ${ARGN} )
endif()

endmacro()