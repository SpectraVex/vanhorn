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
		TraceLog(LOG_INFO, "Unloading Objects..."); 
		for (unsigned int i = 0; i < sizeof(instance->objects) / (sizeof(Object)); i++) {
			TraceLog(LOG_INFO, "Unloading Object: %s", instance->objects[i]->id); 
		}
	}
}

void UpdateLevel() {
	if(instance) {
		for (unsigned int i = 0; i < sizeof(instance->objects) / (sizeof(Object)); i++) {
			UpdateObject(instance->objects[i]);	
		}
	}
}

void RenderLevel() {
	if(instance) {
		DrawGrid(20, 2.0f);
		for (unsigned int i = 0; i < sizeof(instance->objects) / (sizeof(Object)); i++) {
			RenderObject(instance->objects[i]);	
		}
	}
}