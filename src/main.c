#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raygui.h"

int main(int argc, char** argv) {
    InitWindow(400, 200, "Alfur Controller");
    SetTargetFPS(60);

    int showMessage=0;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if(GuiButton((Rectangle){24, 24, 120, 30}, "#191#ShowMessage")) showMessage=1;

        if(showMessage) {
            int result = GuiMessageBox((Rectangle){85, 70, 250, 100},
                "#191#Message Box", "This is a test", "Nice;Cool");

            if(result >= 0) showMessage = 0; 
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}