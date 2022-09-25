//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#pragma once
#ifndef PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS
#define PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS

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

    struct CollisionTrigger {
        unsigned int ID;
        glm::vec4* center;

        explicit CollisionTrigger(glm::vec4* center);
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

        // Default is to not collide
        template <class T, class U> bool Collide(T*, U*) {
            return false;
        };

        // Box-Box
        template <> bool Collide(CollisionBox* A, CollisionBox* B);

        // Box-Plane
        template <> bool Collide(CollisionBox* A, CollisionPlane* B);
        template <> bool Collide(CollisionPlane* B, CollisionBox* A) {
            return Collide(A, B);
        };

        // Sphere-Sphere
        template <> bool Collide(CollisionSphere* A, CollisionSphere* B);

        // Sphere-Plane
        template <> bool Collide(CollisionSphere* A, CollisionPlane* B);
        template <> bool Collide(CollisionPlane* B, CollisionSphere* A) {
            return Collide(A, B);
        };

        // Sphere-Box
        template <> bool Collide(CollisionBox* A, CollisionSphere* B);
        template <> bool Collide(CollisionSphere* B, CollisionBox* A) {
            return Collide(A, B);
        };

        // Function will try to move the collider's position
        // Returns wheter it moved or not
        template<class T> bool TryMove(T* collision, glm::vec4 direction, float speed, float delta);
    };
}

#endif //PENGUINCAFE_COLLISIONS_SRC_HEADERS_PHYSICS
