//
// Created by Nicolle on 9/14/2022.
//

#pragma once
#ifndef PENGUINCAFE_MODEL_SRC_HEADERS_LOADING
#define PENGUINCAFE_MODEL_SRC_HEADERS_LOADING

#include "loading.hpp"
#include "tiny_obj_loader.h"
#include "glm/vec3.hpp"

// Estrutura que representa um modelo geométrico carregado a partir de um
// arquivo ".obj". Veja https://en.wikipedia.org/wiki/Wavefront_.obj_file .
struct ObjectModel {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Este construtor lê o modelo de um arquivo utilizando a biblioteca tinyobjloader.
    // Veja: https://github.com/syoyo/tinyobjloader
    explicit ObjectModel(const char *filename, const char *basepath = NULL, bool triangulate = true);
};

// Estrutura que guarda os triangulos computados do object model
struct ObjectTriangles {
    size_t first_index{}; 			// Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t num_indices{}; 			// Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum rendering_mode{}; 			// Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint vertex_array_object_id{};  // ID do VAO onde estão armazenados os atributos do modelo
    glm::vec3 bbox_min{}; 			// Ponto (0, 0, 0) da bounding box
    glm::vec3 bbox_max{};				// Ponto (1, 1, 1) da bounding box

    ObjectTriangles() = default;
    explicit ObjectTriangles(const char *filepath);
};

#endif //PENGUINCAFE_MODEL_SRC_HEADERS_LOADING
