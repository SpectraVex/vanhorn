/***************************************************************************************************************************
* Vanhorn - A minimal native 3D horror brawler written purely in C99 using raylib, designed to be fast, simple and portable.
****************************************************************************************************************************/

// Vanhorn Includes
#include "vanhorn/common.h"
#include "vanhorn/resource.h"
#include "vanhorn/object.h"

// Look into global static stack-allocated memory blocks for the entire application! No heap allocation, that way we can fit the entire app into a block of contiguous memory.
//static Resources Res;

void CenterWindow() {
    int monitor = GetCurrentMonitor();

    int x = GetMonitorWidth(monitor) / 2 - GetScreenWidth() / 2;
    int y = GetMonitorHeight(monitor) / 2 - GetScreenHeight() / 2; 
    
    SetWindowPosition(x, y);
}

const RenderTexture LoadScaledRenderTarget(const float Percentage) {
    RenderTexture Target = { 0 };
    Target = LoadRenderTexture(GetScreenWidth() * Percentage, GetScreenHeight() * Percentage);

    return Target;
}

int main(void) {
    InitWindow(WINDOWWIDTH, WINDOWHEIGHT, "Vanhorn - Build v1.0");
    SetTargetFPS(144);
    CenterWindow();
    InitAudioDevice();

    //float animatedRotationAngle = 0.0f;
    bool bSpin = false;

    // Init camera.
    Camera3D camera = {};
    camera.position = (Vector3){ 5.0f, 3.0f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 70.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    RenderTexture RenderTarget = LoadScaledRenderTarget(RENDER_PERCENTAGE);

    const Transform world_origin = {(Vector3){0,0,0}, (Vector4){0,0,0,1}, (Vector3){.1,.1,.1}};
    const Transform world_origin2 = {(Vector3){0,0,3}, (Vector4){0,0,0,1}, (Vector3){1,1,1}};
    // Init resources.
    Scene scene = {0};
    LoadResources(&scene);
    AddObject(&scene, world_origin, scene.models[0], 0);
    AddObject(&scene, world_origin2, scene.models[1], 1);
    AddObject(&scene, world_origin2, scene.models[2], 2);
    
    // Main loop.
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, 4);

        /*if(IsKeyPressed(KEY_F)) {
            HideCursor();
            ToggleFullscreen();
        }*/

        if(IsKeyPressed(KEY_R))
            bSpin = !bSpin;
        if(bSpin) {
            UpdateScene(&scene);
        }


        // Update rendering
        BeginDrawing();
            BeginTextureMode(RenderTarget);
            ClearBackground(BLACK);
            BeginMode3D(camera);
                RenderScene(&scene);
            EndMode3D();
            EndTextureMode();

            DrawTexturePro(
                RenderTarget.texture, 
                (Rectangle) { 0,0, (float)RenderTarget.texture.width, (float)-RenderTarget.texture.height },
                (Rectangle) { 0,0, (float)GetScreenWidth(), (float)GetScreenHeight() },
                Vector2Zero(),
                0,
                WHITE);
            DrawFPS(0, GetScreenHeight() - 20);
        EndDrawing();
    }

    // De-Initialization
    UnloadModel(scene.objects[0]->model);
    UnloadModel(scene.objects[1]->model);
    UnloadMusicStream(scene.music_tracks[0]);
    UnloadRenderTexture(RenderTarget);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}