//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#ifndef PENGUINCAFE_STRUCTS_HEADERS_GLOBALS
#define PENGUINCAFE_STRUCTS_HEADERS_GLOBALS

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "tiny_obj_loader.h"

// Estrutura que representa um modelo geométrico carregado a partir de um
// arquivo ".obj". Veja https://en.wikipedia.org/wiki/Wavefront_.obj_file .
struct ObjModel {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	// Este construtor lê o modelo de um arquivo utilizando a biblioteca tinyobjloader.
	// Veja: https://github.com/syoyo/tinyobjloader
	explicit ObjModel(const char *filename, const char *basepath = NULL, bool triangulate = true);
};

// Definimos uma estrutura que armazenará dados necessários para renderizar
// cada objeto da cena virtual.
struct SceneObject {
	std::string name;        // Nome do objeto
	size_t first_index; // Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
	size_t num_indices; // Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
	GLenum rendering_mode; // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
	GLuint vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
	glm::vec3 bbox_min; // Axis-Aligned Bounding Box do objeto
	glm::vec3 bbox_max;
};

#endif //PENGUINCAFE_STRUCTS_HEADERS_GLOBALS
