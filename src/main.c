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

    if(ble_init())
        return 1;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if(GuiButton((Rectangle){(SCREEN_WIDTH/2)-50, (SCREEN_HEIGHT/2)-20, 100, 40}, "Start Scan")) {
            //start scanning
            printf("Button Pressed\n");
            ble_start_scan();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}