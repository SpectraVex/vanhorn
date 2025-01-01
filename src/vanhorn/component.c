#include "component.h"
#include "object.h"
#include "level.h"

bool AddComponent(struct Object* parent, const enum ComponentType type) {
	if(!parent) return false;

	if(parent->num_of_components >= MAX_OBJECT_COMPONENTS) return false;

	// No need to heap allocate, seeing as components are merely struct data stored inside of a heap-allocated object.
	Component component;// = calloc(1, sizeof(Component));
	//if(!component) return false;

	SetRandomSeed(parent->id);
	component.id = GetRandomValue(0, 65000);
	component.transform = parent->transform;
	component.parent = parent;
	component.type = type;

	// Copy of this struct into the array, no heap allocation, just a copy is all that's needed at the moment.
	parent->components[parent->num_of_components] = component;
	parent->num_of_components++;
	TraceLog(LOG_INFO, "VANHORN: Component created.");

	return true;
}

bool UpdateComponent(Component component) {
	return true;
}

void RenderComponent(Component component) {
	//if(!component.type == MODEL) return false;
	/*const Vector2 screen_debug_pos = GetWorldToScreen(component.parent->transform.translation, *GetPlayerCamera());
    const char* component_info = "Component";
    //DrawText(component_info, screen_debug_pos.x, screen_debug_pos.y, 10, LIME);
    float sin_val = sin(GetTime());
    const float x = Clamp(sin_val,1,5);
    DrawPixelV(screen_debug_pos,GREEN);*/
}