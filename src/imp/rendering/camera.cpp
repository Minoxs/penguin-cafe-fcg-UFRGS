//
// Created by Nicolle on 9/7/2022.
//

#include "rendering/camera.hpp"
#include "matrices.h"

glm::mat4 ComputeCamera(Camera camera) {
    return Matrix_Camera_View(camera.position, camera.viewVector, camera.upVector);
}
