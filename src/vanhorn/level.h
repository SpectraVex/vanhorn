#pragma once

#include "common.h"

typedef struct Level {
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