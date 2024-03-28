#include "object.h"
#include "level.h"
#include "resource.h"

Object* AddObject(const Transform transform, const unsigned int model_index) {
	Level* level = GetLevel();
	if(level) {
		if(level->num_of_objects < MAX_OBJECTS) {
			Object* object = (Object*)calloc(1, sizeof(Object));
			SetRandomSeed(GetTime());
			object->id = GetRandomValue(0, MAX_OBJECTS);
			object->transform = transform;
			object->model = GetModelResource(model_index);

			level->objects[level->num_of_objects] = object;
			level->num_of_objects++;
			return object;
		}
	}
	return NULL;
}

void RemoveObject(Object* object) {
	// TODO	
}

void UpdateObject(struct Object* object) {
    if(object) {
    	float rand_offset = 0.0;//Lerp(0.0, 1.0, (float)object->id/MAX_OBJECTS);
    	// Circle movement.
        object->transform.translation.x = cos(GetTime()+rand_offset) * 4;
        object->transform.translation.z = sin(GetTime()+rand_offset) * 4;

        // Define the rotation axis
        const Vector3 rotation_axis = (Vector3){0.0, 1.0, 0.0};
        
        // Determine rotation angle based on elapsed time to ensure smooth rotation
        // Assuming you want to rotate the object 180 degrees per second
        const float angleDegreesPerSecond = -90;
        //float deltaTime = GetFrameTime(); // Time since last frame in seconds
        float angleThisFrame = angleDegreesPerSecond * GetTime(); // Angle to rotate this frame
        
        // Create a rotation quaternion for this frame's rotation
        Quaternion rotatorThisFrame = QuaternionFromAxisAngle(rotation_axis, angleThisFrame * DEG2RAD); // Convert degrees to radians
        
        // Apply the rotation by quaternion multiplication
        // The new rotation is the product of the current rotation and this frame's rotation
        object->transform.rotation = QuaternionMultiply(object->transform.rotation, rotatorThisFrame);
        
        // Optionally, normalize the quaternion to avoid floating-point drift over time
        object->transform.rotation = QuaternionNormalize(object->transform.rotation);
    }
}


void RenderObject(struct Object* object) {
	if(object) {
		const Quaternion qrt = QuaternionFromEuler(object->transform.rotation.z, object->transform.rotation.y, object->transform.rotation.x);
		const Vector3 rotation_axis = (Vector3) {qrt.x, qrt.y, qrt.z};
		DrawModelEx(object->model, 
			object->transform.translation,
			rotation_axis, 
			0.0,
			object->transform.scale,
			WHITE);
		DebugObject(object);
	}
}

void DebugObject(struct Object* object) {
	if(IsCursorHidden()) return;
	// If line traced, then draw text about the object and such.	
	Ray ray = {0};
	RayCollision collision = {0};

	if(!collision.hit) {
		ray = GetScreenToWorldRay(GetMousePosition(), *GetPlayerCamera());
		//collision = GetRayCollisionMesh()
	}
	const Vector2 mouse_pos = GetMousePosition();
    const int font_size = 20;
    const char str[256] = "GameObject";

    DrawText(TextFormat(str), mouse_pos.x, mouse_pos.y, font_size, LIME);

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
*/	BoundingBox box = GetModelBoundingBox(object->model);
	const Vector3 extents = Vector3Subtract(box.max,  box.min);
	DrawCubeWires(object->transform.translation, extents.x, extents.y, extents.z, LIME);
}