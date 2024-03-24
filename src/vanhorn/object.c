#include "object.h"

void AddObject(Scene* scene, const Transform transform, const Model model, const unsigned int array_index) {
	Object* object = (Object*) malloc(sizeof(Object));
	if(scene && object) {
		// This should be hashed to avoid existing IDs.
		scene->objects[array_index] = object;
		object->id = GetRandomValue(0, MAXOBJECTS);
		object->transform = transform;
		object->model = model;
	}
}

void UpdateObject(Object* object) {
	if(object) {
		object->transform.translation.x += 1.0f * GetFrameTime();
		object->model.transform = MatrixRotateXYZ((Vector3){ 0.0f, GetTime(), 0.0f });
	}
}

void RenderObject(Object* object) {
	if(object) {
		//rlPushMatrix();
		DrawModel(object->model, (Vector3)object->transform.translation, 0.2f, WHITE);
		//rlPopMatrix();
	}
}