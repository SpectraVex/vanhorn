/***************************************************************************************************************************
* Vanhorn - A minimal native 3D horror brawler written purely in C99 using raylib, designed to be fast, simple and portable.
****************************************************************************************************************************/
#define RAYGUI_IMPLEMENTATION

// Vanhorn Includes
#include "vanhorn/common.h"
#include "vanhorn/resource.h"
#include "vanhorn/level.h"
#include "vanhorn/object.h"

void CenterWindow() {
    const int monitor = GetCurrentMonitor();

    const int x = GetMonitorWidth(monitor) / 2 - GetScreenWidth() / 2;
    const int y = GetMonitorHeight(monitor) / 2 - GetScreenHeight() / 2; 
    
    SetWindowPosition(x, y);
}

// Might be best to integrate into resources?
const RenderTexture LoadScaledRenderTarget(const float Percentage) {
    RenderTexture target = { 0 };
    target = LoadRenderTexture(GetScreenWidth() * Percentage, GetScreenHeight() * Percentage);
    SetTextureFilter(target.texture, 0);

    return target;
}

int main(void) {
    // Init window.
    InitWindow(WINDOWWIDTH, WINDOWHEIGHT, "Vanhorn - Build v1.0");
    CenterWindow();
    Image icon = LoadImage("D:/Studio/Games/vanhorn/res/tex/icon_cube.png");
    SetWindowIcon(icon);
    HideCursor();
    SetTargetFPS(144);
    InitAudioDevice();

    SetMousePosition(GetScreenWidth()*.5f,GetScreenHeight()*.5f);
    RenderTexture rt = LoadScaledRenderTarget(RENDER_PERCENTAGE);

    // Global resources.
    // For the time being these are essentially everything we'll ever need for the entire game session.
    // Later we can get this to load and unload from a level_#.txt list, or something like that.
    LoadResources();
    GetLevel();
    GetPlayerCamera();
    // AddObject looper for testing spawning multiple objects.
    const Transform world_transform = {(Vector3){0.0, 0.0, 0.0}, (Vector4){0.0, 0.0, 0.0, 1.0}, (Vector3){1.0, 1.0, 1.0}};
    const unsigned int num = 160;
    const float distance = 100.0f;
    for (unsigned int i = 0; i <= num; i++) {
        const float lerpval = (1.0/(float)num)*(float)i;
        const Vector3 pos = Vector3Lerp((Vector3){-distance, 0.0, -4.0}, (Vector3){distance, 0.0, 4.0}, lerpval);
        const Quaternion rot = (Quaternion){0,0,0,1};
        const Vector3 scale = (Vector3){1,1,1};
        const Transform t = (Transform) {pos, rot, scale};

        AddObject(t, 0);
        AddObject(t, 1);
    }

    const Vector3 pos = (Vector3){0.0, 0.0, 0.0};
    const Quaternion rot = (Quaternion){0,0,0,1};
    const Vector3 scale = (Vector3){1,1,1};
    const Transform t = (Transform) {pos, rot, scale};

    // Main loop.
    while (!WindowShouldClose()) {
        UpdateLevel();

        if(IsKeyPressed(KEY_F)) { HideCursor(); ToggleFullscreen(); }

        BeginDrawing();
            BeginTextureMode(rt);
                ClearBackground(BLACK);
                BeginMode3D(*GetPlayerCamera());
                    RenderLevel();
                EndMode3D();
            EndTextureMode();

            // UI
            DrawTexturePro(
                rt.texture, 
                (Rectangle) { 0,0, (float)rt.texture.width, (float)-rt.texture.height },
                (Rectangle) { 0,0, (float)GetScreenWidth(), (float)GetScreenHeight() },
                Vector2Zero(),
                0,
                DARKGRAY);
            DrawFPS(5, 5);
        EndDrawing();
    }

    // De-Initialization
    UnloadRenderTexture(rt);
    UnloadLevel();
    UnloadResources();
    free(GetResources());
    CloseAudioDevice();
    UnloadImage(icon);
    CloseWindow();

    return 0;
}