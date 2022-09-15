//
// Created by Nicolle on 9/7/2022.
//
#pragma once
#ifndef PENGUINCAFE_CAMERA_SRC_IMP_PLAYER
#define PENGUINCAFE_CAMERA_SRC_IMP_PLAYER

#include "rendering.hpp"

#include "glm/vec4.hpp"
#include "glm/ext/matrix_float4x4.hpp"

struct Camera : ObjectInstance {
    inline static const glm::vec4 upVector {0.0f, 1.0f, 0.0f, 0.0f};

    explicit Camera(const ObjectInstance &object);

    glm::mat4 GetViewMatrix() const;
    void Draw() override;
};

struct LookAtCamera : Camera {
    glm::vec4* lookAtPoint;

    explicit LookAtCamera(const ObjectInstance &object, glm::vec4* lookAtPoint);

    void Proc(float time, float delta) override;
};

struct Player : Camera {
    inline static const float speed {1.0f};

    explicit Player(const ObjectInstance &object);

    void cameraTranslate(float delta);
    void cameraPan();
    void Proc(float time, float delta) override;
    void Draw() override;
};

#endif //PENGUINCAFE_CAMERA_SRC_IMP_PLAYER
