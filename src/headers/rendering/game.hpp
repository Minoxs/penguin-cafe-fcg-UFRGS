//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_GAME_HEADERS_RENDERING
#define PENGUINCAFE_GAME_HEADERS_RENDERING

#include "rendering.hpp"

struct Food : ObjectInstance {
    float remaining = 100.0f;

    Physics::InteractiveCollider* interact;
    explicit Food(ObjectInstance const &object, float radius);
    void TryPutInTable();
};

struct Table : ObjectInstance {
    Physics::InteractiveCollider* interact;
    Food* food = nullptr;
    explicit Table(ObjectInstance const &object);
    void PutFood(Food* food);

    void Proc(float, float) override;
};

struct Customer : ObjectInstance {
    float spawnTimer;
    bool isBuying = false;
    float amountEaten = 0.0f;
    float initialRotation;

    Table* tableReference;

    explicit Customer(ObjectInstance const &object, Table* tableReference);

    void Proc(float time, float delta) override;
    void Draw() override;
};


#endif //PENGUINCAFE_GAME_HEADERS_RENDERING
