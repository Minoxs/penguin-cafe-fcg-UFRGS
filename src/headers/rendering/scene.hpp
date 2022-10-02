//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
#define PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING

#include "glad/glad.h"
#include "rendering.hpp"
#include "player.hpp"
#include "physics.hpp"

struct Scene {
    std::map<std::string, ObjectInstance*> virtualScene {};
    Camera* mainCamera;

    Physics::Engine* engine;

    Player* player;
    LookAtCamera* lookAtCamera;

    explicit Scene();

    void addToScene(ObjectInstance* object, bool addBoxCollider = false, float boundingBoxScale = 1.0f);
    void addToScene(ObjectInstance* object, float radius);

    void Render(float time, float delta);
};

#endif //PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
