/***************************************************************************************************************************
* Vanhorn - A minimal native 3D horror brawler written purely in C99 using raylib, designed to be fast, simple and portable.
****************************************************************************************************************************/

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

Camera3D InitCamera() {
    Camera3D camera = {};
    camera.position = (Vector3){ 7.0f, 5.0f, 0.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 3.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 70.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    return camera;
}

int main(void) {
    // Init window.
    InitWindow(WINDOWWIDTH, WINDOWHEIGHT, "Vanhorn - Build v1.0");
    CenterWindow();
    Image icon = LoadImage("D:/Studio/Games/vanhorn/res/tex/icon_cube.png");
    SetWindowIcon(icon);
    HideCursor();
    //SetTargetFPS(144);
    InitAudioDevice();

    SetMousePosition(GetScreenWidth()*.5f,GetScreenHeight()*.5f);
    Camera3D camera = InitCamera();
    RenderTexture rt = LoadScaledRenderTarget(RENDER_PERCENTAGE);

    // Global resources.
    // For the time being these are essentially everything we'll ever need for the entire game session.
    // Later we can get this to load and unload from a level_#.txt list, or something like that.
    GetResources();
    LoadResources();

    // AddObject looper for testing spawning multiple objects.
    const Transform world_transform = {(Vector3){0.0, 0.0, 0.0}, (Vector4){0.0, 0.0, 0.0, 1.0}, (Vector3){1.0, 1.0, 1.0}};
    const unsigned int num = 128;
    const float distance = 100.0f;
    for (unsigned int i = 0; i <= num; i++) {
        const float lerpval = (1.0/(float)num)*(float)i;
        TraceLog(LOG_INFO, "The Percentage Lerp Value: %f", lerpval);
        const Vector3 pos = Vector3Lerp((Vector3){-distance, 0.0, 0.0}, (Vector3){distance, 0.0, 0.0}, lerpval);
        const Quaternion rot = (Quaternion){0,0,0,1};
        const Vector3 scale = (Vector3){.1,.1,.1};
        const Transform t = (Transform) {pos, rot, scale};

        AddObject(t, 1);
    }

    // Main loop.
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, 4);
        SetMousePosition(GetScreenWidth()*.5f,GetScreenHeight()*.5f); 

        UpdateLevel();

        //if(IsKeyPressed(KEY_F)) { HideCursor(); ToggleFullscreen(); }

        // Update rendering
        BeginDrawing();
            BeginTextureMode(rt);
                ClearBackground(BLACK);
                BeginMode3D(camera);
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