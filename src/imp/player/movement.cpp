//
// Created by Nicolle on 9/7/2022.
//

#include "player/movement.hpp"
#include "player/input.hpp"
#include "matrices.h"

void cameraTranslate(Camera* camera, float delta, float speed) {
    glm::vec4 d = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (g_isWPressed) d.z += 1.0f;
    if (g_isSPressed) d.z -= 1.0f;
    if (g_isAPressed) d.x -= 1.0f;
    if (g_isDPressed) d.x += 1.0f;

    float dNorma = norm(d);
    if (dNorma == 0.0f) return;

    d /= dNorma;
    d *= speed * delta;

    if (d.z != 0.0f) {
        camera->position += d.z * camera->viewVector;
    }

    if (d.x != 0.0f) {
        glm::vec4 sideVector = crossproduct(camera->viewVector, camera->upVector);
        camera->position += d.x * (sideVector/norm(sideVector));
    }
}

void ComputeMovement(Camera* camera, float delta) {
    const float speed = 5.0f;
    cameraTranslate(camera, delta, speed);

    glm::vec4 camera_lookat_l = glm::vec4(0.0f, 0.0f, 0.0f,1.0f);
    camera->viewVector = (camera_lookat_l - camera->position)/norm(camera_lookat_l - camera->position);
}