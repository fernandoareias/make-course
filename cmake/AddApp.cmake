macro(add_app_custom app_name)

set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE APP_SOURCES 
    "${APP_DIR}/*.c"
    "${APP_DIR}/*.cpp"
    "${APP_DIR}/*.h"
    "${APP_DIR}/*.hpp"
)

add_executable(${app_name} ${APP_SOURCES})


endmacro()