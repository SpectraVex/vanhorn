#include "object.h"
#include "level.h"
#include "resource.h"

Object* AddObject(const Transform transform, const unsigned int model_index) {
	Level* level = GetLevel();
	if(level) {
		if(level->num_of_objects < MAX_OBJECTS) {
			Object* object = (Object*)calloc(1, sizeof(Object));
			if(object) {
				TraceLog(LOG_INFO, "VANHORN: Object created.");

				// Possibly a better way of getting a random object-unique seed value, fine for now.
				const uintptr_t seed = (uintptr_t)((unsigned char*)object + sizeof(Object));
				SetRandomSeed(seed);

				object->id = GetRandomValue(0, 99999999);
				object->transform = transform;
				object->model = GetModelResource(model_index);

				AddComponent(object, MODEL);

				level->objects[level->num_of_objects] = object;
				level->num_of_objects++;

				return object;
			}
			else TraceLog(LOG_ERROR, "VANHORN: Failed to create object!");
		}
		else TraceLog(LOG_WARNING, "VANHORN: Max number of objects reached!");
	}
	return NULL;
}

void RemoveObject(Object* object) {
	if(object) {
		TraceLog(LOG_INFO, "VANHORN: Removing Object with ID: %d.", object->id);
		for (unsigned int i = 0; i < object->num_of_components; i++) {
			// Shouldn't really have to remove this component seeing as it's just a struct on the heap allocated object.
			//RemoveComponent(component);
		}
		free(object);
	}
}

void UpdateObject(struct Object* object) {
    if(object) {
    	float rand_value_x = Clamp((float)object->id/65000,-1,1);
    	float rand_value_z = Clamp((float)GetRandomValue(0, 65000)/65000,-1,1);

    	float rand_x = Lerp(-1.0, 1.0, rand_value_x);
    	float rand_z = Lerp(-1.0, 1.0, rand_value_z);

    	// Circle movement.
        object->transform.translation.x += rand_x*.01;
        object->transform.translation.z += rand_z*.01;

        // Define the rotation axis
        //const Vector3 rotation_axis = (Vector3){0.0, 1.0, 0.0};
        
        // Determine rotation angle based on elapsed time to ensure smooth rotation
        // Assuming you want to rotate the object 180 degrees per second
        //const float angleDegreesPerSecond = -90;
        //float deltaTime = GetFrameTime(); // Time since last frame in seconds
        //float angleThisFrame = angleDegreesPerSecond * GetTime(); // Angle to rotate this frame
        
        // Create a rotation quaternion for this frame's rotation
        //Quaternion rotatorThisFrame = QuaternionFromAxisAngle(rotation_axis, angleThisFrame * DEG2RAD); // Convert degrees to radians
        
        // Apply the rotation by quaternion multiplication
        // The new rotation is the product of the current rotation and this frame's rotation
        //object->transform.rotation = QuaternionMultiply(object->transform.rotation, rotatorThisFrame);
        
        // Optionally, normalize the quaternion to avoid floating-point drift over time
        //object->transform.rotation = QuaternionNormalize(object->transform.rotation);

		for (unsigned int i = 0; i < object->num_of_components; i++) {
			//Component component = object->components[i];
			UpdateComponent(object->components[i]);
		}
	}
}


void RenderObject(struct Object* object, const bool render_debug_info) {
	if(object) {
		const Quaternion qrt = QuaternionFromEuler(object->transform.rotation.z, object->transform.rotation.y, object->transform.rotation.x);
		const Vector3 rotation_axis = (Vector3) {qrt.x, qrt.y, qrt.z};
		DrawModelEx(object->model, 
			object->transform.translation,
			rotation_axis, 
			0.0,
			object->transform.scale,
			WHITE);

		if (render_debug_info) {
			RenderObjectInfo(object);
		}

		for (unsigned int i = 0; i < object->num_of_components; i++) {
			RenderComponent(object->components[i]);
		}
	}
}

void RenderObjectInfo(struct Object* object) {
	if(IsCursorHidden()) return;
	// If line traced, then draw text about the object and such.	
	Ray ray = {0};
	RayCollision collision = {0};

	const Matrix m = MatrixIdentity();
	const Mesh mesh = object->model.meshes[0];
	const BoundingBox bbox = GetModelBoundingBox(object->model);

	ray = GetScreenToWorldRay(GetMousePosition(), *GetPlayerCamera());
	collision = GetRayCollisionMesh(ray, mesh, m);

	if(collision.hit) {
		const Vector3 extents = Vector3Subtract(bbox.max,  bbox.min);
		DrawCubeWires(object->transform.translation, extents.x, extents.y, extents.z, LIME);

		const Vector2 mouse_pos = GetMousePosition();
	    const int font_size = 15;
	    const char* debug_info = "object ID: #";
	    DrawText(TextFormat("%s\n", debug_info), mouse_pos.x, mouse_pos.y - 15, font_size, LIME);
	}
	
/*    char buffer[512]; // Ensure this buffer is large enough for your text
    
    // Format the transform details into the buffer
    snprintf(buffer, sizeof(buffer), "Pos: [% .2f, % .2f, % .2f]\nRot: [% .2f, % .2f, % .2f]\nScale: [% .2f, % .2f, % .2f]",
             object->transform.translation.x, object->transform.translation.y, object->transform.translation.z,
             object->transform.rotation.x, object->transform.rotation.y, object->transform.rotation.z,
             object->transform.scale.x, object->transform.scale.y, object->transform.scale.z);

    // Use multiple DrawText calls if you want to handle newlines manually or draw each line separately for better control over spacing
    
    int currentY = mouse_pos.y;
    char* line = strtok(buffer, "\n");
    while (line != NULL) {
        DrawText(line, mouse_pos.x, mouse_pos.y, font_size, GREEN);
        currentY += font_size + 2; // Adjust spacing based on your font size, +2 for some extra space
        line = strtok(NULL, "\n");
    }

	DrawText(line, mouse_pos.x, mouse_pos.y, font_size, GREEN);       // Draw text (using default font)
*/
}	