//
// Created by Nicolle on 9/5/2022.
//
#pragma once
#ifndef PENGUINCAFE_OBJECT_SRC_RENDERING
#define PENGUINCAFE_OBJECT_SRC_RENDERING
#include "rendering.hpp"
#include "loading.hpp"

#include "glad/glad.h"
#include "tiny_obj_loader.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "physics/collisions.hpp"

// Guarda os dados de uma instância de um objeto da cena
// Pode-se utilizar o mesmo objeto múltiplas vezes
struct ObjectInstance {
    // Name must be unique for each instance
    std::string name;
    Scene* sceneReference = nullptr;

    // Pointer to object's descriptor of triangles
    // Can be shared between many instances
    ObjectTriangles* triangles;

    // Variables to control model matrix
    glm::vec4 position{};
    glm::vec4 rotation{};
    glm::vec4 scale{1.0f, 1.0f, 1.0f, 0.0f};

    // Variables to control textures
    GLint DiffuseTextureID = 0;
    glm::vec3 Ks {0.0f, 0.0f, 0.0f};
    float SpecularExponent = 1.0f;

    // Physics stuff
    Physics::Collider* collider = nullptr;

    // Copy constructor ClassName(ClassName const &copyFrom)
    ObjectInstance(ObjectInstance const &object);
    // Creates an instance of a scene object
    explicit ObjectInstance(const char* name, ObjectTriangles* triangles);
    explicit ObjectInstance(const char* name, glm::vec4 position, glm::vec4 rotation, ObjectTriangles* triangles);

    virtual void Proc(float time, float delta);

    virtual void Draw();
};

struct BezierCurve {
    glm::vec4 p1 {};
    glm::vec4 p2 {};
    glm::vec4 p3 {};
    glm::vec4 p4 {};

    bool reverse = false;

    explicit BezierCurve(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4);

    glm::vec4 calculate(float t) const;
};

struct BezierObject : public ObjectInstance {
    BezierCurve* curve;
    float currentPosition = 0.0f;
    float timeStuck = 0.0f;

    explicit BezierObject(const ObjectInstance &object, BezierCurve* curve);

    void Proc(float time, float delta) override;
};

#ifdef DEBUG
struct DebugObject : public ObjectInstance {
    const char* name;
    int positionIndex;
    bool writing = false;

    explicit DebugObject(const ObjectInstance &object, const char* name);

    void writePosition();
    void Proc(float time, float delta) override;
};
#endif // DEBUG

void PrintObjModelInfo(ObjectModel* model); // Função para debugging

#endif //PENGUINCAFE_OBJECT_SRC_RENDERING
