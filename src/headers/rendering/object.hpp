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

// Guarda os dados de uma instância de um objeto da cena
// Pode-se utilizar o mesmo objeto múltiplas vezes
struct ObjectInstance {
    std::string name;

    glm::vec3 position{};
    glm::vec3 rotation{};

    ObjectTriangles* triangles{};

    // Copy constructor ClassName(ClassName const &copyFrom)
    ObjectInstance(ObjectInstance const &object);
    // Creates an instance of a scene object
    explicit ObjectInstance(const char* name, glm::vec3 position, glm::vec3 rotation, ObjectTriangles* triangles);

    virtual void Proc(float time, float delta);

    virtual void Draw();
};

struct RotatingObject : public ObjectInstance {
    // Constructor from parent from
    explicit RotatingObject(const ObjectInstance &object);

    void Proc(float time, float delta) override;
};

void PrintObjModelInfo(ObjectModel* model); // Função para debugging

#endif //PENGUINCAFE_OBJECT_SRC_RENDERING
