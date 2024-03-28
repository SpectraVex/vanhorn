#include "level.h"
#include "object.h"

static Level* instance = NULL;

Level* GetLevel() {
    if (!instance) {
        instance = (Level*)calloc(1, sizeof(Level));
        TraceLog(LOG_INFO, "VANHORN: Level instantiated.");
    }
    return instance;
}

void UnloadLevel() {
	if(instance) {
		if(instance->player_camera) {
			free(instance->player_camera);	
		}

		TraceLog(LOG_INFO, "Unloading Objects..."); 
		for (unsigned int i = 0; i < sizeof(instance->objects) / (sizeof(Object)); i++) {
			TraceLog(LOG_INFO, "Unloading Object: %s", instance->objects[i]->id); 
			RemoveObject(instance->objects[i]);
		}
	}
}

Camera3D* GetPlayerCamera() {
	if(instance) {
		if(!instance->player_camera) {
			Camera3D* camera = (Camera3D*)calloc(1, sizeof(Camera3D));
			camera->position = (Vector3){ 7.0f, 5.0f, 0.0f };    // Camera position
    		camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    		camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    		camera->fovy = 70.0f;                                // Camera field-of-view Y
    		instance->player_camera = camera;
			return instance->player_camera;
		}
		return instance->player_camera;
	}
	return NULL;	
}

void UpdateLevel() {
	if(instance) {
		// Update player camera
		if(instance->player_camera) {
        	// Toggle inspection controls
        	if(IsKeyPressed(KEY_TAB)) IsCursorHidden() ? EnableCursor() : DisableCursor();
        	//if(IsKeyPressed(KEY_TAB)) IsCursorHidden() ? SetMouseCursor(MOUSE_CURSOR_DEFAULT) : SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			if(IsCursorHidden()) UpdateCamera(instance->player_camera, CAMERA_FREE);
		    if(IsCursorHidden()) SetMousePosition(GetScreenWidth()*.5f,GetScreenHeight()*.5f); 
		}

		// Update level objects	
		for (unsigned int i = 0; i < sizeof(instance->objects) / (sizeof(Object)); i++) {
			UpdateObject(instance->objects[i]);	
		}
	}
}

void RenderLevel() {
	if(instance) {
		DrawGrid(20, 1.0f);
		for (unsigned int i = 0; i < sizeof(instance->objects) / (sizeof(Object)); i++) {
			RenderObject(instance->objects[i]);	
		}
	}
}