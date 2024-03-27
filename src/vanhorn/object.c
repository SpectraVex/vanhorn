#include "object.h"
#include "level.h"
#include "resource.h"

void AddObject(const Transform transform, const unsigned int model_index) {
	if(GetLevel()) {
		if(GetLevel()->num_of_objects < MAX_OBJECTS) {
			Object* object = (Object*)calloc(1, sizeof(Object));
			object->id = GetRandomValue(0, MAX_OBJECTS);
			object->transform = transform;
			object->model = GetModelResource(model_index);

			GetLevel()->objects[GetLevel()->num_of_objects] = object;
			GetLevel()->num_of_objects++;
			return;
		}
	}
}

void UpdateObject(struct Object* object) {
	if(object) {
		object->transform.translation.x += cos(sin(object->transform.translation.x + GetTime())) * GetFrameTime();
		object->model.transform = MatrixRotateXYZ((Vector3){ 0.0f, cos(object->transform.translation.x / 3.0), 0.0f });
	}
}

void RenderObject(struct Object* object) {
	if(object) {
		rlPushMatrix();
			rlTranslatef(object->transform.translation.x, object->transform.translation.y, object->transform.translation.z);
			rlRotatef(0.0, object->transform.rotation.x, object->transform.rotation.y, object->transform.rotation.z);
			rlScalef(object->transform.scale.x, object->transform.scale.y, object->transform.scale.z);
				DrawModelEx(object->model, 
					(Vector3) {0,0,0}, 
					// Need to figure out the math here for correct per object rotation.
					(Vector3) {0,1,0}, 
					0.0f,
					object->transform.scale,
					WHITE);
		rlPopMatrix();
	}
}