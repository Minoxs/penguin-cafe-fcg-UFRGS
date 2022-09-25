//
// Created by Nicolle on 9/7/2022.
//

#include "rendering.hpp"

#include "matrices.h"
#include "global.hpp"


Camera::Camera(const ObjectInstance &object) : ObjectInstance(object) {

}

glm::mat4 Camera::GetViewMatrix() const {
    return Matrix_Camera_View(position, rotation, upVector);
}

void Camera::Draw() {

}

LookAtCamera::LookAtCamera(const ObjectInstance &object, glm::vec4 *lookAtPoint) : Camera(object) {
    this->lookAtPoint = lookAtPoint;
}

void LookAtCamera::Proc(float time, float delta) {
    const glm::vec4 diff = glm::vec4(*lookAtPoint - position);
    rotation = diff/norm(diff);
}


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
    d *= speed * delta;

    // TODO CONVERT DIRECTION INTO CAMERA COORDINATE SYSTEM



//    if (d.z != 0.0f) {
//        position += d.z * rotation;
//    }
//
//    if (d.x != 0.0f) {
//        glm::vec4 sideVector = crossproduct(rotation, upVector);
//        position += d.x * (sideVector/norm(sideVector));
//    }
}

void Player::cameraPan() {
    float x = std::cos(g_CameraPhi) * std::sin(g_CameraTheta);
    float y = std::sin(-g_CameraPhi);
    float z = std::cos(g_CameraPhi) * std::cos(g_CameraTheta);

    rotation  = glm::vec4(x, y, z, 0.0f);
    rotation /= norm(rotation);
}

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
