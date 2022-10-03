//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_CHARACTER_HEADERS_PLAYER
#define PENGUINCAFE_CHARACTER_HEADERS_PLAYER

#include "player.hpp"
#include "rendering.hpp"

struct Player : ObjectInstance {
    inline static const float speed {10.0f};

    Camera* view = nullptr;
    Physics::InteractiveCollider* hand = nullptr;
    Physics::InteractiveCollider* holding = nullptr;
    float grabTime = 0.0f;

    explicit Player(const ObjectInstance &object, Camera* view);

    void cameraTranslate(float delta);
    void cameraPan();

    void Proc(float time, float delta) override;
    void Draw() override;
};

#endif //PENGUINCAFE_CHARACTER_HEADERS_PLAYER
