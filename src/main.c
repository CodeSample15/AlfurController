#include <stdio.h>
#include <stdlib.h>

#include "raylib.h" //installed
#include "raygui.h" //lib/raygui

#include "bluetooth.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 300

int main(int argc, char** argv) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Alfur Controller");
    SetTargetFPS(60);

    if(check_for_ble_adapters())
        return 1;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}