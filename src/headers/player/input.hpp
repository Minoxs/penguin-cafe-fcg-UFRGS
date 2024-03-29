//
// Created by Nicolle on 9/5/2022.
//
#pragma once
#ifndef PENGUINCAFE_INPUT_HEADERS_PLAYER
#define PENGUINCAFE_INPUT_HEADERS_PLAYER

#include "player.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Variáveis globais que armazenam a última posição do cursor do mouse, para
// que possamos calcular quanto que o mouse se movimentou entre dois instantes
// de tempo. Utilizadas no callback CursorPosCallback() abaixo.

extern double g_LastCursorPosX;
extern double g_LastCursorPosY;

// "g_LeftMouseButtonPressed = true" se o usuário está com o botão esquerdo do mouse
// pressionado no momento atual. Veja função MouseButtonCallback().

extern bool g_LeftMouseButtonPressed;
extern bool g_RightMouseButtonPressed;
extern bool g_MiddleMouseButtonPressed;

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.

extern float g_CameraTheta;
extern float g_CameraPhi;
extern float g_CameraDistance;

// Variáveis que controlam rotação do antebraço
extern float g_ForearmAngleZ;
extern float g_ForearmAngleX;

// Variáveis que controlam translação do torso
extern float g_TorsoPositionX;
extern float g_TorsoPositionY;

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
extern float g_AngleX;
extern float g_AngleY;
extern float g_AngleZ;

extern bool g_isWPressed;
extern bool g_isSPressed;
extern bool g_isAPressed;
extern bool g_isDPressed;
extern bool g_isEPressed;
extern bool g_isGPressed;
extern bool g_isKPressed;

extern bool g_is0Pressed;
extern bool g_is1Pressed;
extern bool g_is2Pressed;
extern bool g_is3Pressed;
extern bool g_is4Pressed;
extern bool g_is5Pressed;
extern bool g_is6Pressed;
extern bool g_is7Pressed;
extern bool g_is8Pressed;
extern bool g_is9Pressed;

void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void ErrorCallback(int error, const char *description);
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif //PENGUINCAFE_INPUT_HEADERS_PLAYER
