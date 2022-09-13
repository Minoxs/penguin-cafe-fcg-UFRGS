//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#ifndef PENGUINCAFE_STRUCTS_HEADERS_GLOBALS
#define PENGUINCAFE_STRUCTS_HEADERS_GLOBALS

#include "glad/glad.h"
#include "tiny_obj_loader.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/ext/matrix_float4x4.hpp"

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
struct RenderObject {
	int ID;
	size_t first_index; 			// Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
	size_t num_indices; 			// Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
	GLenum rendering_mode; 			// Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
	GLuint vertex_array_object_id;  // ID do VAO onde estão armazenados os atributos do modelo
	glm::vec3 bbox_min; 			// Ponto (0, 0, 0) da bounding box
	glm::vec3 bbox_max;				// Ponto (1, 1, 1) da bounding box
};

// Guarda os dados de uma instância de um objeto da cena
// Pode-se utilizar o mesmo objeto múltiplas vezes
struct SceneObject {
	std::string name;

	glm::vec3 position;
	glm::vec3 rotation;

	RenderObject* triangles;
};

#endif //PENGUINCAFE_STRUCTS_HEADERS_GLOBALS
