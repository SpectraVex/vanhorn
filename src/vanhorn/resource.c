#include "resource.h"

// Singleton.
static Resources* instance = NULL;

Resources* GetResources() {
    if(instance == NULL) {
        instance = (Resources*)calloc(1, sizeof(Resources));
        TraceLog(LOG_INFO, "VANHORN: Resources instantiated.");
    }
    return instance;
}

void LoadResources() {
	if(instance) {
		if(instance->num_of_models < MAX_OBJECTS) {
			instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/stalker/stalker_low.glb");
			instance->num_of_models++;

			instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/male_character_ps1-style.glb");
			instance->num_of_models++;

			TraceLog(LOG_INFO, "VANHORN: All resources loaded.");
		}
	}
}

void UnloadResources() {
	if(instance) {
		for(unsigned int i = 0; i < instance->num_of_models; i++) {
			UnloadModel(instance->models[i]);
		}
		TraceLog(LOG_INFO, "VANHORN: All resources unloaded.");
	}
}

Model GetModelResource(const unsigned int index) {
	if(instance) {
		if(index >= 0 && index < instance->num_of_models) {
			if(IsModelReady(instance->models[index])) {
				return instance->models[index];
			}
		}
	}
	Model empty_model = {0};
	return empty_model;
}