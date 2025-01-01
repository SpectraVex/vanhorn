#include "level.h"
#include "object.h"

// Singleton.
static Level* instance = NULL;

bool CreateLevel() {
    if (!instance) {
        instance = calloc(1, sizeof(Level));
        if(instance) {
        	TraceLog(LOG_INFO, "VANHORN: Level instantiated.");
        	return true;
        } else return false;
    }
    return (instance != NULL) ? true : false;
}

void LoadLevel() {
	GetPlayerCamera();
}

void UnloadLevel() {
	if(instance) {
		// Free the player camera.
		if(instance->player_camera) {
			free(instance->player_camera);	
		}

		// Free all objects.
		TraceLog(LOG_INFO, "VANHORN: Unloading objects..."); 
		for (unsigned int i = 0; i < instance->num_of_objects; i++) {
			TraceLog(LOG_INFO, "Unloading Object: %s", instance->objects[i]->id); 
			RemoveObject(instance->objects[i]);
		}
		instance->num_of_objects = 0;
		free(instance);
		return;
	}
    TraceLog(LOG_ERROR, "VANHORN: Failed to unload level!");
}

Level* GetLevel() {
	return instance;
}

Camera3D* GetPlayerCamera() {
	if(instance) {
		if(!instance->player_camera) {
			Camera3D* camera = (Camera3D*)calloc(1, sizeof(Camera3D));
			if(camera) {
				camera->position = (Vector3){ 7.0f, 5.0f, 0.0f };    // Camera position
    			camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    			camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    			camera->fovy = FOV;                                // Camera field-of-view Y
    			instance->player_camera = camera;

				return instance->player_camera;
			}
			return NULL;
		}
		return instance->player_camera;
	}
	return NULL;
}

bool EmptyLevel() {
	if(instance) {
		for (unsigned int i = 0; i < instance->num_of_objects; i++) {
			RemoveObject(instance->objects[i]);
		}
		instance->num_of_objects = 0;
		TraceLog(LOG_INFO, "VANHORN: Level Emptied."); 
		return true;
	}
	return false;
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
		for (unsigned int i = 0; i < instance->num_of_objects; i++) {
			UpdateObject(instance->objects[i]);	
		}
	}
}

void RenderLevel(const bool render_debug_info) {
	if(instance) {
		DrawGrid(32, 1.0f);
		for (int i = 0; i < instance->num_of_objects; i++) {
			RenderObject(instance->objects[i], render_debug_info);	
		}	
	}
}