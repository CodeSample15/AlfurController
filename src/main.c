#include <stdio.h>
#include <stdlib.h>

#include "raylib.h" //installed
#include "raygui.h" //lib/raygui

#include "utils.h"
#include "bluetooth.h"

int main(int argc, char** argv) {
    const int FPS = 60;

    //setup screen
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Alfur Controller");
    SetTargetFPS(FPS);

    //attempt to start simpleble library
    if(ble_init())
        return 1;

    //for ble scans
    int isScanning = 0;
    float scanProgress = 0;

    //main loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        switch(isScanning) {
            case 0:
                if(GuiButton(CENTERED_RECT(FULL_SCREEN_RECT, 100, 40, 0, 0), "Start Scan")) {
                    //start scanning
                    isScanning = 1;     //set scanning flag to get rid of this button
                    scanProgress = 0;
                    ble_start_scan();   //non blocking: runs new pthread
                }
                break;
            case 1:
                GuiLabel(CENTERED_RECT(FULL_SCREEN_RECT, 200, 40, 0, -40), "Scanning...");
                GuiProgressBar(CENTERED_RECT(FULL_SCREEN_RECT, 200, 40, 0, 0),
                                    "0%", "100%", &scanProgress, 0, BLE_SCAN_TIME);
                     
                //cancel button for windows only, sorry (stopping threads in Linux apparently is broken)
                #if _WIN32
                if(GuiButton(CENTERED_RECT(FULL_SCREEN_RECT, 100, 40, 0, 40), "Stop")) {
                    isScanning = 0;
                    ble_stop_scan();
                }
                #endif

                scanProgress += 1 / ((float)FPS / 1000);
                if(scanProgress >= BLE_SCAN_TIME) isScanning = 0;
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}