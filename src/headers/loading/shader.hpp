//
// Created by Nicolle on 9/5/2022.
//
#pragma once
#ifndef PENGUINCAFE_SHADER_HEADERS_LOADING
#define PENGUINCAFE_SHADER_HEADERS_LOADING

#include "loading.hpp"
#include "glad/glad.h"

void LoadShader(const char *filename, GLuint shader_id);
GLuint LoadShader_Vertex(const char *filename);
GLuint LoadShader_Fragment(const char *filename);
void LoadShadersFromFiles();
void LoadTextureImage(const char *filename);

#endif //PENGUINCAFE_SHADER_HEADERS_LOADING
