//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_GAME_HEADERS_RENDERING
#define PENGUINCAFE_GAME_HEADERS_RENDERING

#include "rendering.hpp"

struct Table : ObjectInstance {
    glm::vec4 foodPosition {};

    explicit Table(ObjectInstance const &object, glm::vec4 foodPosition);
};

struct Customer : ObjectInstance {
    const char* tableName;
    float spawnTimer;
    bool isBuying = false;

    explicit Customer(ObjectInstance const &object, const char* tableName);

    void Proc(float time, float delta) override;
    void Draw() override;
};

struct Food : ObjectInstance {
    Physics::InteractiveCollider* interact;
    explicit Food(ObjectInstance const &object, float radius);
};

#endif //PENGUINCAFE_GAME_HEADERS_RENDERING