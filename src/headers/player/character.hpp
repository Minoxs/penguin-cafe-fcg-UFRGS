//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_CHARACTER_HEADERS_PLAYER
#define PENGUINCAFE_CHARACTER_HEADERS_PLAYER

#include "player.hpp"
#include "rendering.hpp"

struct Player : Camera {
    inline static const float speed {10.0f};

    explicit Player(const ObjectInstance &object);

    void cameraTranslate(float delta);
    void cameraPan();
    void Proc(float time, float delta) override;
    void Draw() override;
};

#endif //PENGUINCAFE_CHARACTER_HEADERS_PLAYER
