#pragma once

#include "common.h"
#include "resource.h"

typedef struct Scene {
	// Resources
	Model models[MAXMODELS];
	Music music_tracks[3];

	// Objects
	struct Object* objects[MAXOBJECTS];
} Scene;

void UpdateScene(Scene* scene);
void RenderScene(Scene* scene);