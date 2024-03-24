#pragma once

#include "common.h"
#include "scene.h"

typedef struct Object {
    unsigned int id;
	Transform transform;
	Model model;
} Object;

void AddObject(Scene* scene, const Transform transform, const Model model, const unsigned int array_index);

void UpdateObject(Object* object);
void RenderObject(Object* object);