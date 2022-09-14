//
// Created by Nicolle on 9/7/2022.
//

#include "rendering.hpp"

#include "matrices.h"

glm::mat4 Camera::GetViewMatrix() const {
    return Matrix_Camera_View(this->position, this->viewVector, this->upVector);
}
