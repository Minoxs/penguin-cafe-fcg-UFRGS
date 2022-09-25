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

// TODO IMPLEMENT FUNCTIONS

// This physics engine uses Axis-Aligned Bounding-Boxes (AAAB)
// Basically, collision things only have position and no rotation
// This might allow some clipping between models, but will be much faster to compute
// Since this engine is highly unoptimized, speede is key
namespace Physics {
    enum Alignment {
        X,
        Y,
        Z
    };

    // TODO RENAME TO COLLIDER
    struct CollisionTrigger {
        // Uniquely identifies trigger (used to ignore "self-collision")
        unsigned int ID;
        // Layer where collisions will happen
        Engine* layer;
        // Point associated with collider
        glm::vec4* center;

        explicit CollisionTrigger(glm::vec4* center);

        // Moves object if there are no collisions
        // Returns wheter it moved or not
        virtual bool TryMove(glm::vec4 direction, float speed, float delta);

        // Functions to check collisions
        // Always returns false in the base class
        virtual bool Collide(CollisionPlane* B);
        virtual bool Collide(CollisionBox* B);
        virtual bool Collide(CollisionSphere* B);
    };

    struct CollisionPlane : CollisionTrigger {
        Alignment align;
        float length;
        float height;

        CollisionPlane(glm::vec4* center, Alignment align, float length, float height);
    };

    struct CollisionSphere : CollisionTrigger {
        float radius;

        CollisionSphere(glm::vec4* center, float radius);
        bool TryMove(glm::vec4 direction, float speed, float delta) override;
    };

    struct CollisionBox : CollisionTrigger {
        float lengthX;
        float lengthY;
        float lengthZ;

        CollisionBox(glm::vec4* center, float lengthX, float lengthY, float lengthZ);
        CollisionBox(glm::vec4* center, glm::vec3 bboxMin, glm::vec3 bboxMax);
    };

    struct Engine {
        Engine() = default;

        // This is probably a dumb idea
        std::list<CollisionBox*> boxes;
        std::list<CollisionSphere*> spheres;
        std::list<CollisionPlane*> planes;

        // Add objects to the list
        void AddBox(CollisionBox* box);
        void AddSphere(CollisionSphere* sphere);
        void AddPlane(CollisionPlane* plane);

        // Checks if given object collides with other
        // tracked objects in the engine
        bool CheckCollision(CollisionTrigger* check);
    };
}

#endif //PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS
