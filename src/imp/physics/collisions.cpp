//
// Created by Nicolle on 9/25/2022.
//

#include "physics.hpp"
#include "physics/collisions.hpp"
#include "matrices.h"

#include <cmath>

int triggersNum = 0;

namespace Physics {
    bool collide(ColliderSphere* S, ColliderBox* B) {
        glm::vec4 closestPoint = glm::vec4(
                std::max(B->bboxMin.x, std::min(S->center->x, B->bboxMax.x)),
                std::max(B->bboxMin.y, std::min(S->center->y, B->bboxMax.y)),
                std::max(B->bboxMin.z, std::min(S->center->z, B->bboxMax.z)),
                1.0f
        );

        float distance = norm(closestPoint - *S->center);

        return distance < S->radius;
    }

    Collider::Collider(glm::vec4* center) {
        this->ID = triggersNum;
        this->center = center;

        triggersNum += 1;
    }

    // TODO: BABYYY
    bool Collider::TryMove(glm::vec4 direction, float speed, float delta) {
        return false;
    }

    bool Collider::Collide(ColliderPlane *B) {
        return false;
    }

    bool Collider::Collide(ColliderBox *B) {
        return false;
    }

    bool Collider::Collide(ColliderSphere *B) {
        return false;
    }

    ColliderPlane::ColliderPlane(glm::vec4* center, Alignment align, float length, float height) : Collider(center) {
        this->align = align;
        this->length = length;
        this->height = height;
    }

    ColliderSphere::ColliderSphere(glm::vec4* center, float radius) : Collider(center) {
        this->radius = radius;
    }

    // Esfera com Esfera
    bool ColliderSphere::Collide(ColliderSphere* B) {
        return norm(*this->center - *B->center) <= (this->radius + B->radius);
    }

    // Esfera com Cubo
    bool ColliderSphere::Collide(ColliderBox* B) {
        return collide(this, B);
    }

    ColliderBox::ColliderBox(glm::vec4* center, float lengthX, float lengthY, float lengthZ) : Collider(center) {
        glm::vec3 offset = glm::vec3(lengthX/2, lengthY/2, lengthZ/2);
        glm::vec3 origin = glm::vec3(center->x, center->y, center->z);

        this->bboxMin = origin - offset;
        this->bboxMax = origin + offset;
    }

    ColliderBox::ColliderBox(glm::vec4* center, glm::vec3 bboxMin, glm::vec3 bboxMax) : Collider(center) {
        glm::vec3 origin = glm::vec3(center->x, center->y, center->z);

        this->bboxMin = origin + bboxMin;
        this->bboxMax = origin + bboxMax;
    }



    // Cubo com Cubo
    bool ColliderBox::Collide(ColliderBox* B) {
        return (
                (this->bboxMin.x <= B->bboxMax.x) &&
                (this->bboxMax.x >= B->bboxMin.x) &&
                (this->bboxMin.y <= B->bboxMax.y) &&
                (this->bboxMax.y >= B->bboxMin.y) &&
                (this->bboxMin.z <= B->bboxMax.z) &&
                (this->bboxMax.z >= B->bboxMin.z)
        );
    }

    // Cubo com Esfera
    bool ColliderBox::Collide(ColliderSphere* S) {
        return collide(S, this);
    }

    // TODO BABY TOO
    bool ColliderBox::TryMove(glm::vec4 direction, float speed, float delta) {
        return Collider::TryMove(direction, speed, delta);
    }

    void Engine::Add(ColliderBox* box) {
        box->layer = this;
        this->boxes.push_back(box);
    }

    void Engine::Add(ColliderSphere* sphere) {
        sphere->layer = this;
        this->spheres.push_back(sphere);
    }

    void Engine::Add(ColliderPlane* plane) {
        plane->layer = this;
        this->planes.push_back(plane);
    }

    bool Engine::CheckCollision(Collider* check) {
        for (ColliderBox* box : this->boxes) {
            if (check->Collide(box)) {
                return true;
            }
        }

        for (ColliderSphere* sphere : this->spheres) {
            if (check->Collide(sphere)) {
                return true;
            }
        }

        for (ColliderPlane* plane : this->planes) {
            if (check->Collide(plane)) {
                return true;
            }
        }

        return false;
    }
}
