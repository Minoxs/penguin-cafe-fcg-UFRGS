//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_TEXT_HEADERS_RENDERING
#define PENGUINCAFE_TEXT_HEADERS_RENDERING

#include "rendering.hpp"

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"

void TextRendering_Init();

float TextRendering_LineHeight(GLFWwindow *window);

float TextRendering_CharWidth(GLFWwindow *window);

void TextRendering_PrintString(GLFWwindow *window, const std::string &str, float x, float y, float scale = 1.0f);

void TextRendering_PrintMatrix(GLFWwindow *window, glm::mat4 M, float x, float y, float scale = 1.0f);

void TextRendering_PrintVector(GLFWwindow *window, glm::vec4 v, float x, float y, float scale = 1.0f);

void TextRendering_PrintMatrixVectorProduct(GLFWwindow *window, glm::mat4 M, glm::vec4 v, float x, float y,
                                            float scale = 1.0f);

void TextRendering_PrintMatrixVectorProductMoreDigits(GLFWwindow *window, glm::mat4 M, glm::vec4 v, float x, float y,
                                                      float scale = 1.0f);

void TextRendering_PrintMatrixVectorProductDivW(GLFWwindow *window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

// Funções abaixo renderizam como texto na janela OpenGL algumas matrizes e
// outras informações do programa. Definidas após main().
void TextRendering_ShowModelViewProjection(GLFWwindow *window, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec4 p_model);

void TextRendering_ShowEulerAngles(GLFWwindow *window);

void TextRendering_ShowProjection(GLFWwindow *window);

void TextRendering_ShowFramesPerSecond(GLFWwindow *window);

#endif //PENGUINCAFE_TEXT_HEADERS_RENDERING
