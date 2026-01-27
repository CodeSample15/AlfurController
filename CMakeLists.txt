cmake_minimum_required(VERSION 3.28)

PROJECT (AlfurController)

add_compile_options(-Wall -Werror -DRAYGUI_IMPLEMENTATION)

find_package(simpleble REQUIRED CONFIG)

include_directories( include "lib/raygui/src" "lib/simpleble/simplecble/include/simplecble")
file( GLOB SOURCES "src/*.c" )

add_executable( 
    AlfurController
        ${SOURCES}
)

target_link_libraries(AlfurController simpleble::simpleble -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)