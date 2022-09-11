//
// Created by Nicolle on 9/7/2022.
//

#ifndef PENGUINCAFE_CAMERA_SRC_IMP_PLAYER
#define PENGUINCAFE_CAMERA_SRC_IMP_PLAYER

#include "glm/vec4.hpp"
#include "glm/ext/matrix_float4x4.hpp"

struct Camera {
    glm::vec4 position;
    glm::vec4 viewVector;
    glm::vec4 upVector;
    glm::vec4 lookAtPoint;

    glm::mat4 GetViewMatrix() const;
};

#endif //PENGUINCAFE_CAMERA_SRC_IMP_PLAYER
