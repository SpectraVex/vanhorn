#pragma once

#include "common.h"

struct Level;

typedef struct Object {
    unsigned int id;
	Transform transform;
	Model model;
} Object;

void AddObject(const Transform transform, const unsigned int model_index);

void UpdateObject(struct Object* object);
void RenderObject(struct Object* object);