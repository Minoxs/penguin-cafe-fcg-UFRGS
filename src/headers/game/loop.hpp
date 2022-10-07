//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_LOOP_HEADERS_GAME
#define PENGUINCAFE_LOOP_HEADERS_GAME

#include "game.hpp"
#include "rendering.hpp"

struct Game {
    inline static const float rollTime = 10.0f;
    inline static const std::vector<std::string> foods {
        "apple",
        "croissant",
        "tea",
        "cake"
    };
    Scene* scene;
    float lastRoll;

    Game();
    void Step(float time, float delta);
};

#endif //PENGUINCAFE_LOOP_HEADERS_GAME
