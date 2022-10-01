//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS
#define PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS

#include "physics.hpp"
#include <list>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

// This physics engine uses Axis-Aligned Bounding-Boxes (AAAB)
// Basically, collision things only have position and no rotation
// This might allow some clipping between models, but will be much faster to compute
// Since this engine is highly unoptimized, speede is key
namespace Physics {
    struct Collider {
        // Uniquely identifies trigger (used to ignore "self-collision")
        unsigned int ID;
        // Layer where collisions will happen
        Engine* layer = nullptr;
        // Point associated with collider
        glm::vec4* center;

        explicit Collider(glm::vec4* center);

        // Moves object if there are no collisions
        // Returns wheter it moved or not
        virtual bool TryMove(glm::vec4 offset, bool checkCollision);

        // Functions to check collisions
        // Always returns false in the base class
        virtual bool Collide(ColliderBox* B);
        virtual bool Collide(ColliderSphere* B);
    };

    struct ColliderSphere : Collider {
        float radius;

        ColliderSphere(glm::vec4* center, float radius);
        bool Collide(ColliderBox* B) override;
        bool Collide(ColliderSphere* B) override;
    };

    struct ColliderBox : Collider {
        glm::vec3 bboxMin {};
        glm::vec3 bboxMax {};

        ColliderBox(glm::vec4* center, float lengthX, float lengthY, float lengthZ);
        ColliderBox(glm::vec4* center, glm::vec3 bboxMin, glm::vec3 bboxMax);

        bool TryMove(glm::vec4 offset, bool checkCollision) override;
        bool Collide(ColliderBox* B) override;
        bool Collide(ColliderSphere* B) override;
    };

    struct Engine {
        Engine() = default;

        // This is probably a dumb idea
        std::list<ColliderBox*> boxes;
        std::list<ColliderSphere*> spheres;

        // Add objects to the list
        void Add(ColliderBox* box);
        void Add(ColliderSphere* sphere);

        // Checks if given object collides with other
        // tracked objects in the engine
        bool CheckCollision(Collider* check);
    };
}

#endif //PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS
