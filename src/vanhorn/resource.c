#include "resource.h"

// Singleton.
static Resources* instance = NULL;

bool CreateResources() {
    if(instance == NULL) {
        instance = (Resources*)calloc(1, sizeof(Resources));
        TraceLog(LOG_INFO, "VANHORN: Resources instantiated.");
    }
    return (instance != NULL) ? true : false;
}

void LoadResources() {
	if(instance) {
		if(instance->num_of_models < MAX_MODELS) {
			// Model 1.
			instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/silent_hill_1_meshes_-_harry_mason.glb");
			instance->num_of_models++;

			// Model 2.
			instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/worn_bandages.glb");
			instance->num_of_models++;

			// Model 3.
			//instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/silent_hill_1_meshes_-_harry_mason.glb");
			//instance->num_of_models++;

			// Model 4.
			//instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/fire_axe.glb");
			//instance->num_of_models++;

			TraceLog(LOG_INFO, "VANHORN: All resources loaded.");
		}
		return;
	}
	TraceLog(LOG_ERROR, "VANHORN: Failed to load resources!");
}

void UnloadResources() {
	if(instance) {
		for(unsigned int i = 0; i < instance->num_of_models; i++) {
			UnloadModel(instance->models[i]);
		}
		instance->num_of_models = 0;
		TraceLog(LOG_INFO, "VANHORN: All resources unloaded.");
	}
}

Resources* GetResources() {
	return instance;
}

Model GetModelResource(const unsigned int index) {
	if(instance) {
		if(index >= 0 && index < instance->num_of_models) {
			if(IsModelReady(instance->models[index])) {
				return instance->models[index];
			}
		}
	}
	Model null_model = {0};
	return null_model;
}