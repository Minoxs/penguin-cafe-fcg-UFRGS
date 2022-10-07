//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_GAME_HEADERS_RENDERING
#define PENGUINCAFE_GAME_HEADERS_RENDERING

#include "rendering.hpp"


struct InteractiveObject : ObjectInstance {
    Physics::InteractiveCollider* interact = nullptr;
    explicit InteractiveObject(ObjectInstance const &object);
};

struct Food : InteractiveObject {
    float remaining = 100.0f;
    float foodValue = 1.0f;

    explicit Food(ObjectInstance const &object, float radius);
    ~Food();

    void TryPutInTable();
};

struct Table : InteractiveObject {
    Food* food = nullptr;

    explicit Table(ObjectInstance const &object);
    
    void PutFood(Food* food);
    void Proc(float, float) override;
};

struct Customer : InteractiveObject {
    inline static const float SpawnDelay = 5.0f;
    float initialRotation;
    glm::vec4 customerFaceDirection;

    float spawnTimer;
    bool isBuying = false;
    bool waitingForPayment = false;
    float amountEaten = 0.0f;

    Table* tableReference;

    explicit Customer(ObjectInstance const &object, Table* tableReference);
    float GetMoney();

    void Proc(float time, float delta) override;
    void Draw() override;
};


#endif //PENGUINCAFE_GAME_HEADERS_RENDERING
