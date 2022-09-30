//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "player.hpp"
#include "global.hpp"
#include "matrices.h"

Player::Player(const ObjectInstance &object) : Camera(object) {

}

void Player::cameraTranslate(float delta) {
    glm::vec4 d = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (g_isWPressed) d.z += 1.0f;
    if (g_isSPressed) d.z -= 1.0f;
    if (g_isAPressed) d.x -= 1.0f;
    if (g_isDPressed) d.x += 1.0f;

    float dNorma = norm(d);
    if (dNorma == 0.0f) return;

    d /= dNorma;

    glm::vec4 offset = {};

    if (d.z != 0.0f) {
        offset += d.z * rotation;
    }

    if (d.x != 0.0f) {
        glm::vec4 sideVector = crossproduct(rotation, upVector);
        offset += d.x * (sideVector/norm(sideVector));
    }

    offset /= norm(offset);

    collider->TryMove(offset * speed * delta, true);
}

void Player::cameraPan() {
    float x = std::cos(g_CameraPhi) * std::sin(g_CameraTheta);
    float y = std::sin(-g_CameraPhi);
    float z = std::cos(g_CameraPhi) * std::cos(g_CameraTheta);

    rotation  = glm::vec4(x, y, z, 0.0f);
    rotation /= norm(rotation);
}

// TODO ATENDER PENGUIN APERTANDO E
// TODO PEGAR COMIDA NA COZINHA
// TODO LEVAR COMIDA ATE PENGUIN
// TODO GANHAR DINHEIRO
void Player::Proc(float time, float delta) {
    cameraTranslate(delta);
    cameraPan();
}

void Player::Draw() {
    // TODO: Implement first person

    // Rendering third person
    if (!g_UseFreeCamera) {
        ObjectInstance::Draw();
    }
}
