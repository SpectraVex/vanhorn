#pragma once

#include "common.h"

typedef struct Level {
	// We should have a player set of files, the camera should't be apart of the level here, it should be a part of the player struct.
	Camera3D* player_camera;
	unsigned int num_of_objects;
	struct Object* objects[MAX_OBJECTS];
} Level;

bool CreateLevel();
void LoadLevel();
void UnloadLevel();
Level* GetLevel();
Camera3D* GetPlayerCamera();

bool EmptyLevel();
//bool PopulateLevel();

void UpdateLevel();
void RenderLevel(const bool render_debug_info);