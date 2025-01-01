#pragma once

#include "common.h"

// Could have global resources that load when game boots, 
// then inherit from that into LevelResources, that only loads specific extra stuff for that level.
typedef struct Resources {
	unsigned int num_of_models;
	Model models[MAX_MODELS];
} Resources;

bool CreateResources();
void LoadResources();
void UnloadResources();
Resources* GetResources();

// Maybe use index as enum?
Model GetModelResource(const unsigned int index);