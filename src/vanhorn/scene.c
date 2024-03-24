#include "scene.h"
#include "object.h"

void UpdateScene(Scene* scene) {
	if(scene) {
		for (unsigned int i = 0; i < sizeof(scene->objects) / sizeof(Object*); ++i) {
			UpdateObject(scene->objects[i]);	
		}
	}
}

void RenderScene(Scene* scene) {
	if(scene) {
        DrawGrid(10, 1.0f);
		for (unsigned int i = 0; i < sizeof(scene->objects) / sizeof(Object*); ++i) {
			RenderObject(scene->objects[i]);	
		}
	}
}