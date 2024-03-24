#include "resource.h"

void LoadResources(Scene* scene) {
	if(scene) {
		scene->models[0] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/old_couch.glb"); 	
		scene->models[1] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/deadbodies.glb"); 	
		scene->models[2] = LoadModel("D:/Studio/Games/vanhorn/res/tmp/crate.glb"); 	
    	scene->music_tracks[0] = LoadMusicStream("D:/Studio/Games/vanhorn/res/snd/amb_loop_00.wav"); 
	}
}