#pragma once

#include "common.h"

typedef struct Resources {
	unsigned int num_of_models;
	Model models[MAX_MODELS];
} Resources;

Resources* GetResources();
void LoadResources();
void UnloadResources();