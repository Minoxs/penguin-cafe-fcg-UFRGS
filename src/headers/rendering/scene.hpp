//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
#define PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING

#include "rendering.hpp"
#include "glad/glad.h"

void InitializeScene(char* files[], int length);
void RenderScene(Camera *camera, float time, float delta);

#endif //PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
