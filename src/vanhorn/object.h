#pragma once

#include "common.h"

typedef struct Object {
    unsigned int id;
	Transform transform;
	Model model;
} Object;

Object* AddObject(const Transform transform, const unsigned int model_index);
void RemoveObject(Object* object);

void UpdateObject(struct Object* object);
void RenderObject(struct Object* object);
void DebugObject(struct Object* object);