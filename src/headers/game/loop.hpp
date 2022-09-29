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
    Scene* scene;

    // Game context
    //

    Game();
    void Step();
};

#endif //PENGUINCAFE_LOOP_HEADERS_GAME
