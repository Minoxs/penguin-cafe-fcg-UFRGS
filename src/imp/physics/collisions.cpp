//
// Created by Nicolle on 9/25/2022.
//

#include "physics.hpp"
#include "physics/collisions.hpp"
#include "matrices.h"

#include <cmath>
#include <utility>

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

        return (distance < S->radius) != S->inverted;
    }

    // Struct Implementations
    Collider::Collider(glm::vec4* center) {
        this->center = center;
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
        return (norm(*this->center - *B->center) <= (this->radius + B->radius)) != inverted;
    }

    // Esfera com Cubo
    bool ColliderSphere::Collide(ColliderBox* B) {
        return collideSphereBox(this, B);
    }

    ColliderBox::ColliderBox(glm::vec4* center, glm::vec3 bboxMin, glm::vec3 bboxMax, glm::vec4 scale) : Collider(center) {
        const glm::vec4 origin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 offset = *center - origin;

        auto auxBboxMin = glm::vec4(bboxMin, 1.0f);
        auto auxBboxMax = glm::vec4(bboxMax, 1.0f);

        auto matScale = Matrix_Scale(scale.x, scale.y, scale.z);
        auto matTrans = Matrix_Translate(offset.x, offset.y, offset.z);

        this->bboxMin = matTrans * matScale * auxBboxMin;
        this->bboxMax = matTrans * matScale * auxBboxMax;
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

    InteractiveCollider::InteractiveCollider(std::string referenceName, InteractiveType type, glm::vec4* center, float radius) : ColliderSphere(center, radius)  {
        this->referenceName = std::move(referenceName);
        this->type = type;
    }

    void Engine::Add(ColliderBox* box) {
        box->layer = this;
        this->boxes.push_back(box);
    }

    void Engine::Add(ColliderSphere* sphere) {
        sphere->layer = this;
        this->spheres.push_back(sphere);
    }

    void Engine::Add(InteractiveCollider *interact) {
        interact->layer = this;
        interactives.push_back(interact);
    }

    void Engine::Remove(ColliderBox* box) {
        boxes.remove(box);
    }

    void Engine::Remove(ColliderSphere* sphere) {
        spheres.remove(sphere);
    }

    void Engine::Remove(InteractiveCollider* interact) {
        interactives.remove(interact);
    }

    bool Engine::CheckCollision(Collider* check) {
        for (ColliderBox* box : this->boxes) {
            if ((check->center != box->center) && check->Collide(box)) {
                return true;
            }
        }

        for (ColliderSphere* sphere : this->spheres) {
            if ((check->center != sphere->center) && check->Collide(sphere)) {
                return true;
            }
        }

        return false;
    }

    InteractiveCollider* Engine::Interacting(Collider *check) {
        for (InteractiveCollider* interactive : this->interactives) {
            if ((check->center != interactive->center) && check->Collide(interactive)) {
                return interactive;
            }
        }

        return nullptr;
    }

}
