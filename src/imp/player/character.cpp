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
    this->hand = new Physics::InteractiveCollider(this->name, this, Physics::HAND, handPosition, 2.5f);
    this->hand->active = false;
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

    // Remove Y component of movement
    offset.y = 0.0f;
    offset /= norm(offset);

    // Make movement more fluid by separating move tries
    auto move = offset * speed * delta;
    auto moveX = glm::vec4(move.x, 0.0f, 0.0f, 0.0f);
    auto moveZ = glm::vec4(0.0f, 0.0f, move.z, 0.0f);

    if (collider->TryMove(moveX, true)) {
        *hand->center += moveX;
    }

    if (collider->TryMove(moveZ, true)) {
        *hand->center += moveZ;
    }

    view->position.x = position.x;
    view->position.z = position.z;
}

void Player::cameraPan() {
    float x = std::cos(g_CameraPhi) * std::sin(g_CameraTheta);
    float y = std::sin(-g_CameraPhi);
    float z = std::cos(g_CameraPhi) * std::cos(g_CameraTheta);

    view->rotation  = glm::vec4(x, y, z, 0.0f);
    view->rotation /= norm(view->rotation);

    rotation.y = g_CameraTheta + (-90.0f * 3.14159265359f / 180.0f);
    *hand->center = view->position + view->rotation;

    if (food != nullptr) {
        auto holdingPosition = (position + 3.0f * view->rotation);
        auto holdingOffset = holdingPosition - food->position;

        // Move separately so object gets stuck less often
        auto moveX = glm::vec4(holdingOffset.x, 0.0f, 0.0f, 0.0f);
        auto moveY = glm::vec4(0.0f, holdingOffset.y, 0.0f, 0.0f);
        auto moveZ = glm::vec4(0.0f, 0.0f, holdingOffset.z, 0.0f);

        food->collider->TryMove(moveX, true);
        food->collider->TryMove(moveZ, true);
        food->collider->TryMove(moveY, true);
    }
}

void Player::Proc(float time, float delta) {
    cameraTranslate(delta);
    cameraPan();

    // Delete food on demand
    if (g_isGPressed && (time - bounceTime) > 0.5f && food != nullptr) {
        delete food;
        food = nullptr;
    }

    // Grab food
    if (g_isEPressed && (time - bounceTime) > 0.5f) {
        if (food == nullptr) {
            // Check if player is interacting with something
            auto hold = hand->layer->Interacting(hand, Physics::FOOD);
            if (hold != nullptr) {
                hold->active = false;
                food = (Food*) hold->referenceObject;
                food->position.y += food->interact->radius * 1.5f;
                bounceTime = time;
            }
        } else {
            // Only drop food on tables
            if (food->TryPutInTable()) {
                food = nullptr;
            }
            bounceTime = time;
        }

        // Check if trying to get money from customer
        auto hold = hand->layer->Interacting(hand, Physics::CUSTOMER);
        if (hold != nullptr) {
            auto customer = (Customer*) hold->referenceObject;
            money += customer->GetMoney();
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
