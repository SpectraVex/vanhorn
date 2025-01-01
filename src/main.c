/***************************************************************************************************************************
* Vanhorn - A minimal 3D horror brawler written purely in C99 using Raylib, designed to be fast, simple and portable.
****************************************************************************************************************************/
// Vanhorn includes.
#include "vanhorn/common.h"
#include "vanhorn/resource.h"
#include "vanhorn/level.h"
#include "vanhorn/object.h"

// For GUI support.
#define RAYGUI_IMPLEMENTATION

void CenterWindow() {
    const int monitor = GetCurrentMonitor();

    const int x = GetMonitorWidth(monitor) / 2 - GetScreenWidth() / 2;
    const int y = GetMonitorHeight(monitor) / 2 - GetScreenHeight() / 2; 
    
    SetWindowPosition(x, y);
}

void Init(const float WindowWidth, const float WindowHeight, const char* WindowTitle) {
    //SetConfigFlags(/*FLAG_FULLSCREEN_MODE |*/ FLAG_WINDOW_HIGHDPI);
    InitWindow(WindowWidth, WindowHeight, WindowTitle);
    SetTargetFPS(FRAMERATE);
    Image icon = LoadImage("D:/Studio/Games/vanhorn/res/tex/icon_cube.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    CenterWindow();
    HideCursor();
    InitAudioDevice();
    SetMousePosition(GetScreenWidth()*.5f,GetScreenHeight()*.5f);
}

int main(void) {
    // Init window.
    Init(WINDOWWIDTH, WINDOWHEIGHT, "Vanhorn - Build v1.0");

    // Init the main render target.
    RenderTexture render_target = LoadRenderTexture(GetScreenWidth() * RENDER_PERCENTAGE, GetScreenHeight() * RENDER_PERCENTAGE);
    SetTextureFilter(render_target.texture, 1);

    // Global resources.
    // For the time being these are essentially everything we'll ever need for the entire game session.
    // Later we can get this to load and unload from a level_#.txt list, or something like that.
    if(CreateResources()) {
        LoadResources();
    }

    // Game world is simply a level.
    if(CreateLevel()) {
        LoadLevel();
    }

    // AddObject looper for testing spawning multiple objects.
    const Transform default_transform = {(Vector3){0.0, 0.0, 0.0}, (Vector4){0.0, 0.0, 0.0, 1.0}, (Vector3){1.0, 1.0, 1.0}};
    /*const unsigned int num = 160;
    const float distance = 100.0f;
    for (unsigned int i = 0; i <= num; i++) {
        const float lerpval = (1.0/(float)num)*(float)i;
        const Vector3 pos = Vector3Lerp((Vector3){-distance, 0.0, -4.0}, (Vector3){distance, 0.0, 4.0}, lerpval);
        const Quaternion rot = (Quaternion){0,0,0,1};
        const Vector3 scale = (Vector3){1,1,1};
        const Transform t = (Transform) {pos, rot, scale};

        AddObject(t, 0);
        AddObject(t, 1);
    }*/

    _Bool debug_mode = false;
    const Level* level = GetLevel();

    // Temp debug text data.
    //char debug_buffer[24];
    static char debug_text[25] = "number_of_objects = ";
    static char debug_value_buffer[4];

    // Main loop.
    while (!WindowShouldClose()) {
        // Game loop.
        SetRandomSeed(GetTime());
        UpdateLevel();

        //if(IsKeyPressed(KEY_F)) { HideCursor(); ToggleBorderlessWindowed(); }
        const float seed = sin(GetTime());
        SetRandomSeed(seed);

        if(IsKeyDown(KEY_ENTER)) { 
            AddObject(default_transform, GetRandomValue(0,1)); 
        } 
        if(IsKeyPressed(KEY_BACKSPACE)) { EmptyLevel(); } 

        // Render loop.
        BeginDrawing();
            // Core.
            BeginTextureMode(render_target);
                ClearBackground(BLACK);
                BeginMode3D(*GetPlayerCamera());
                if(IsKeyPressed(KEY_TAB)) { debug_mode = !debug_mode; }
                RenderLevel(debug_mode);
                EndMode3D();
            EndTextureMode();

            // Render image & UI.
            DrawTexturePro(
                render_target.texture, 
                (Rectangle) { 0,0, (float)render_target.texture.width, (float)-render_target.texture.height },
                (Rectangle) { 0,0, (float)GetScreenWidth(), (float)GetScreenHeight() },
                Vector2Zero(),
                0,
                WHITE);

            // Draw debug info (For some reason, this is really expensive after spawning many objects?)
            DrawFPS(10, 10);
            if(debug_mode) {
                if(level) {
                    const int value = level->num_of_objects;
                    sprintf(debug_value_buffer,"%d",value);
                    DrawText(debug_value_buffer,10,50,30,WHITE);
                }
            }
        EndDrawing();
    }

    // De-Initialization
    UnloadRenderTexture(render_target);
    UnloadLevel();
    UnloadResources();
    free(GetResources());
    CloseAudioDevice();
    CloseWindow();

    return 0;
}