//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "player.hpp"
#include "global.hpp"
#include "matrices.h"

Player::Player(const ObjectInstance &object, Camera* view) : ObjectInstance(object) {
    this->view = view;
    auto handPosition = new glm::vec4(this->position);
    this->hand = new Physics::InteractiveCollider(this->name, Physics::HAND, handPosition, 2.0f);
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
        offset += d.z * view->rotation;
    }

    if (d.x != 0.0f) {
        glm::vec4 sideVector = crossproduct(view->rotation, Camera::upVector);
        offset += d.x * (sideVector/norm(sideVector));
    }

    offset.y = 0.0f;

    offset /= norm(offset);

    if (collider->TryMove(offset * speed * delta, true)) {
        view->position.x = position.x;
        view->position.z = position.z;
        *hand->center += offset * speed * delta;
    }
}

void Player::cameraPan() {
    float x = std::cos(g_CameraPhi) * std::sin(g_CameraTheta);
    float y = std::sin(-g_CameraPhi);
    float z = std::cos(g_CameraPhi) * std::cos(g_CameraTheta);

    view->rotation  = glm::vec4(x, y, z, 0.0f);
    view->rotation /= norm(view->rotation);

    rotation.y = g_CameraTheta + (-90.0f * 3.14159265359f / 180.0f);
    *hand->center = view->position + view->rotation;
}

// TODO ATENDER PENGUIN APERTANDO E
// TODO PEGAR COMIDA NA COZINHA
// TODO LEVAR COMIDA ATE PENGUIN
// TODO GANHAR DINHEIRO
void Player::Proc(float time, float delta) {
    cameraTranslate(delta);
    cameraPan();

    if (g_isEPressed) {
        // Check if player is interacting with something
        auto hold = hand->layer->Interacting(hand);
        if (hold != nullptr) {
            // TODO DO SOMETHING
            printf("yes!\n");
        }
    }
}

void Player::Draw() {
    // TODO: Implement first person

    // Rendering third person
    if (!g_UseFreeCamera) {
        ObjectInstance::Draw();
    }
}
