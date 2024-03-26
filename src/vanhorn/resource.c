#include "resource.h"

// Singleton resource manager, heap allocated struct of typedef Resources.
Resources* GetResources() {
    static Resources* instance;
    if (instance == NULL) {
        instance = (Resources*)calloc(1, sizeof(Resources));
    }
    return instance;
}

void LoadResources() {
	Resources* instance = GetResources();
	if (instance) {
		if (instance->num_of_models < MAX_OBJECTS) {
			instance->models[instance->num_of_models] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/old_couch.glb"); 	
			instance->num_of_models++;
		}
	}
}

void UnloadResources() {
	Resources* instance = GetResources();
	if (instance) {
		for(unsigned int i = 0; i < instance->num_of_models; i++) {
			UnloadModel(instance->models[i]);
		}
	}
}