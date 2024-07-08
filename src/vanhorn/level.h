#pragma once

#include "common.h"

typedef struct Level {
	// We should have a player set of files, the camera should't be apart of the level here, it should be a part of the player struct.
	Camera3D* player_camera;
	unsigned int num_of_objects;
	struct Object* objects[MAX_OBJECTS];
} Level;

Level* GetLevel();
void UnloadLevel();
Camera3D* GetPlayerCamera();

void EmptyLevel();
void PopulateLevel();

void UpdateLevel();
void RenderLevel();