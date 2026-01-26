cmake_minimum_required(VERSION 3.28)

PROJECT (AlfurController)

add_compile_options(-Wall -Werror -DRAYGUI_IMPLEMENTATION)

include_directories( include "lib/raygui/src" )
file( GLOB SOURCES "src/*.c" )

add_executable( 
    AlfurController
        ${SOURCES}
)

target_link_libraries(AlfurController -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)