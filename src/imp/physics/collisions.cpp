//
// Created by Nicolle on 9/25/2022.
//

#include "physics.hpp"
#include "physics/collisions.hpp"
#include "matrices.h"

#include <cmath>

int triggersNum = 0;

namespace Physics {
    // Internal functions
    bool collideSphereBox(ColliderSphere* S, ColliderBox* B) {
        glm::vec4 closestPoint = glm::vec4(
	        std::max(B->bboxMin.x, std::min(S->center->x, B->bboxMax.x)),
	        std::max(B->bboxMin.y, std::min(S->center->y, B->bboxMax.y)),
	        std::max(B->bboxMin.z, std::min(S->center->z, B->bboxMax.z)),
	        1.0f
        );

        float distance = norm(closestPoint - *S->center);

        return distance < S->radius;
    }

    // Struct Implementations
    Collider::Collider(glm::vec4* center) {
        this->ID = triggersNum;
        this->center = center;

        triggersNum += 1;
    }

    bool Collider::TryMove(glm::vec4 offset, bool checkCollision) {
        glm::vec4 startPosition = *center;

        *center += offset;

        if (checkCollision && layer->CheckCollision(this)) {
            *center = startPosition;
            return false;
        }

        return true;
    }

    bool Collider::Collide(ColliderBox *B) {
        return false;
    }

    bool Collider::Collide(ColliderSphere *B) {
        return false;
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
        return collideSphereBox(this, B);
    }

    ColliderBox::ColliderBox(glm::vec4* center, float lengthX, float lengthY, float lengthZ) : Collider(center) {
        glm::vec3 offset = glm::vec3(lengthX/2, lengthY/2, lengthZ/2);
        glm::vec3 origin = glm::vec3(center->x, center->y, center->z);

        this->bboxMin = origin - offset;
        this->bboxMax = origin + offset;
    }

    ColliderBox::ColliderBox(glm::vec4* center, glm::vec3 bboxMin, glm::vec3 bboxMax, glm::vec4 scale) : Collider(center) {
        const glm::vec4 origin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec3 offset = (*center - origin) * scale;

        this->bboxMin = offset + bboxMin;
        this->bboxMax = offset + bboxMax;
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
        return collideSphereBox(S, this);
    }

    bool ColliderBox::TryMove(glm::vec4 offset, bool checkCollision) {
        glm::vec3 bboxMinBackup = bboxMin;
        glm::vec3 bboxMaxBackup = bboxMax;
        glm::vec3 move = glm::vec3(offset.x, offset.y, offset.z);

        bboxMin += move;
        bboxMax += move;

        if (!Collider::TryMove(offset, checkCollision)) {
            bboxMin = bboxMinBackup;
            bboxMax = bboxMaxBackup;
            return false;
        }

        return true;
    }

    void Engine::Add(ColliderBox* box) {
        box->layer = this;
        this->boxes.push_back(box);
    }

    void Engine::Add(ColliderSphere* sphere) {
        sphere->layer = this;
        this->spheres.push_back(sphere);
    }

    bool Engine::CheckCollision(Collider* check) {
        for (ColliderBox* box : this->boxes) {
            if ( (check->ID != box->ID) && check->Collide(box) ) {
                return true;
            }
        }

        for (ColliderSphere* sphere : this->spheres) {
            if ( (check->ID != sphere->ID) && check->Collide(sphere) ) {
                return true;
            }
        }

        return false;
    }
}
