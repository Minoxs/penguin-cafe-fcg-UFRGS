//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
#define PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING

#include "rendering.hpp"
#include "glad/glad.h"
#include "player.hpp"

struct SceneObject {
    std::map<std::string, ObjectInstance*> virtualScene;
    Camera freeCamera;
    Camera lookAtCamera;
    PlayerObject player;

    SceneObject(SceneObject const &scene);

    explicit SceneObject(Camera freeCamera, Camera lookAtCamera, PlayerObject player);

    void addToScene(ObjectInstance* object);

    void RenderScene(Camera *camera, float time, float delta);
};



void InitializeScene(char* files[], int length);

#endif //PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
