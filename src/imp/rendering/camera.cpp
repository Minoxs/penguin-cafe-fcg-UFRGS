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
