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
    inline static const int maxFoods = 10;

    std::map<std::string, ObjectInstance*> virtualScene {};
    std::map<std::string, Food*> foodCache {};
    Physics::Engine* engine;
    Camera* mainCamera;

    int foodCount = 0;

    Player* player;
    LookAtCamera* lookAtCamera;

    explicit Scene();
    void AddFood(const std::string& name);

    void addToScene(ObjectInstance* object, bool addBoxCollider = false, float boundingBoxScale = 1.0f);
    void addToScene(InteractiveObject* object, bool addBoxCollider = false, float boundingBoxScale = 1.0f);

    void Render(float time, float delta);
};

#endif //PENGUINCAFE_SCENE_SRC_HEADERS_RENDERING
