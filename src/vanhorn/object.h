#pragma once

#include "common.h"
#include "component.h"

typedef struct Object {
    unsigned int id;
	Transform transform;
	// For the time being, we are assuming that every object in the game, is a physical thing with a model.
	Model model;
    unsigned int num_of_components;
	Component components[MAX_OBJECT_COMPONENTS];
} Object;

Object* AddObject(const Transform transform, const unsigned int model_index);
void RemoveObject(Object* object);

void UpdateObject(struct Object* object);
void RenderObject(struct Object* object, const bool render_debug_info);

void RenderObjectInfo(struct Object* object);