//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_VARIABLES_HEADERS_GLOBALS
#define PENGUINCAFE_VARIABLES_HEADERS_GLOBALS

#include "global.hpp"

#include <string>
#include <stack>
#include "glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
extern float g_ScreenRatio;

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
extern bool g_UsePerspectiveProjection;

extern bool g_UseFreeCamera;

// Variável que controla se o texto informativo será mostrado na tela.
extern bool g_ShowInfoText;

extern GLuint g_NumLoadedTextures;

// Variáveis que definem um programa de GPU (shaders). Veja função LoadGenericShaders().
extern GLuint gpu_VertexShaderID;
extern GLuint gpu_FragmentShaderID;
extern GLuint gpu_ProgramID;
extern GLint gpu_ModelUniform;
extern GLint gpu_ViewUniform;
extern GLint gpu_ProjectionUniform;

// Textures in the GPU
extern GLint gpu_TextureDiffuseUniform;
extern GLint gpu_KsUniform;
extern GLint gpu_SpecularExponentUniform;

#endif //PENGUINCAFE_VARIABLES_HEADERS_GLOBALS
