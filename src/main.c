/*******************************************************************************************
*
* Vanhorn - A minimal 3D horror brawler written purely in C99 using raylib.
*
********************************************************************************************/

// Core Dependencies
#include <stdio.h>

// External Dependencies
#include <raylib.h>

// Project
#include "vanhorn/core/vhcore.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 640;
    const int screenHeight = 480;

    const int x = func();

    printf("%i\n", x);

    InitWindow(screenWidth, screenHeight, "Vanhorn - Build v1.0");
    InitAudioDevice();

    Music music = LoadMusicStream("D:/Studio/Games/vanhorn/res/snd/amb_loop_00.wav"); 
    PlayMusicStream(music);

    SetTargetFPS(244);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Welcome to Vanhorn...", 210, 210, 20, DARKGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadMusicStream(music);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}