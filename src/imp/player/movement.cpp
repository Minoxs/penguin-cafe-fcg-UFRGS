//
// Created by Nicolle on 9/7/2022.
//

#include "player/movement.hpp"
#include "player/input.hpp"
#include "matrices.h"
#include "global/variable.hpp"

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

void cameraPan(Camera* camera) {
	float x = std::cos(g_CameraPhi) * std::sin(g_CameraTheta);
	float y = std::sin(-g_CameraPhi);
	float z = std::cos(g_CameraPhi) * std::cos(g_CameraTheta);

	camera->viewVector  = glm::vec4(x, y, z, 0.0f);
	camera->viewVector /= norm(camera->viewVector);
}

void HandleCameraMovement(Camera* camera, float delta) {
    const float speed = 5.0f;

    if (g_UseFreeCamera) {
        cameraTranslate(camera, delta, speed);
        cameraPan(camera);
    } else {
        const glm::vec4 diff = glm::vec4(camera->lookAtPoint - camera->position);
        camera->viewVector = diff/norm(diff);
    }
}
