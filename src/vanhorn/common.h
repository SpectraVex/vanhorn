#pragma once

// Standard Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Raylib
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <raygui.h>

#define GLSL_VERSION 330

// Vanhorn 
#define FRAMERATE 60 // To emulate the ps1.
#define WINDOWWIDTH 1920*1.5//4096*0.9
#define WINDOWHEIGHT 1080*1.5//2160*0.9
#define FOV 90
#define RENDER_PERCENTAGE 0.35

#define MAX_MODELS 512

#define MAX_OBJECTS 1024
#define MAX_OBJECT_COMPONENTS 16