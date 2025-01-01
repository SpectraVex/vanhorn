#pragma once

#include "common.h"

typedef enum ComponentType {
	MODEL,
	BEHAVIOUR,
} ComponentType;

typedef struct Component {
    unsigned int id;
	Transform transform;
	struct Object* parent;
	enum ComponentType type;
	void (*Tick) ();
} Component;

bool AddComponent(struct Object* parent, const enum ComponentType type);
bool RemoveComponent(struct Object* parent, const unsigned int target_component_index);

bool UpdateComponent(Component component);
void RenderComponent(Component component);