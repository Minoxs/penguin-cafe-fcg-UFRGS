//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "game.hpp"

Game::Game() {
    scene = new Scene();
    Step(0, rollTime);
    lastRoll = 0.0f;
}

void Game::Step(float time, float delta) {
    lastRoll += delta;
    if (lastRoll >= rollTime) {
        lastRoll -= rollTime;
        auto dice = rand()%100;
        int pick;

        if      (dice >= 80) pick = 3;
        else if (dice >= 60) pick = 2;
        else if (dice >= 30) pick = 1;
        else                 pick = 0;

        scene->AddFood(foods[pick]);
    }
}
