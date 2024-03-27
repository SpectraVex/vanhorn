#pragma once

#include "common.h"

struct Object;

typedef struct Level {
	unsigned int num_of_objects;
	struct Object* objects[MAX_OBJECTS];
} Level;

Level* GetLevel();
void UnloadLevel();

void UpdateLevel();
void RenderLevel();