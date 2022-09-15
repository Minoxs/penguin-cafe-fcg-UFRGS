//
// Created by Nicolle on 9/5/2022.
//

#include <stdexcept>
#include "rendering.hpp"

#include "glad/glad.h"
#include "matrices.h"
#include "glm/gtc/type_ptr.hpp"

#include "global.hpp"

ObjectInstance::ObjectInstance(const ObjectInstance &object) {
    name = object.name;
    position = object.position;
    rotation = object.rotation;
    triangles = object.triangles;
}

ObjectInstance::ObjectInstance(const char* name, glm::vec3 position, glm::vec3 rotation, ObjectTriangles* triangles) {
    this->name = name;
    this->position = position;
    this->rotation = rotation;
    this->triangles = triangles;
}

void ObjectInstance::Proc(float time, float delta) {

}

// Função que desenha um objeto armazenado em g_VirtualScene. Veja definição
// dos objetos na função BuildTrianglesAndAddToVirtualScene().
void ObjectInstance::Draw() {
	// Calcular a Model matrix
	glm::mat4 model = Matrix_Translate(position.x, position.y, position.z)
						* Matrix_Rotate_Z(rotation.z)
						* Matrix_Rotate_X(rotation.x)
						* Matrix_Rotate_Y(rotation.y);

	// Enviar para GPU
	glUniformMatrix4fv(p_model_uniform, 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(p_object_id_uniform, triangles->ID);

	// "Ligamos" o VAO. Informamos que queremos utilizar os atributos de
	// vértices apontados pelo VAO criado pela função BuildTrianglesAndAddToVirtualScene(). Veja
	// comentários detalhados dentro da definição de BuildTrianglesAndAddToVirtualScene().
	glBindVertexArray(triangles->vertex_array_object_id);

	// Setamos as variáveis "bbox_min" e "bbox_max" do fragment shader
	// com os parâmetros da axis-aligned bounding box (AABB) do modelo.
	glm::vec3 bbox_min = triangles->bbox_min;
	glm::vec3 bbox_max = triangles->bbox_max;
	glUniform4f(p_bbox_min_uniform, bbox_min.x, bbox_min.y, bbox_min.z, 1.0f);
	glUniform4f(p_bbox_max_uniform, bbox_max.x, bbox_max.y, bbox_max.z, 1.0f);

	// Pedimos para a GPU rasterizar os vértices dos eixos XYZ
	// apontados pelo VAO como linhas. Veja a definição de
	// g_VirtualScene[""] dentro da função BuildTrianglesAndAddToVirtualScene(), e veja
	// a documentação da função glDrawElements() em
	// http://docs.gl/gl3/glDrawElements.
	glDrawElements(
			triangles->rendering_mode,
			triangles->num_indices,
			GL_UNSIGNED_INT,
			(void *) (triangles->first_index * sizeof(GLuint))
	);

	// "Desligamos" o VAO, evitando assim que operações posteriores venham a
	// alterar o mesmo. Isso evita bugs.
	glBindVertexArray(0);
}

RotatingObject::RotatingObject(const ObjectInstance &object) : ObjectInstance(object) {

}

void RotatingObject::Proc(float time, float delta) {
    if (rotation.y > 360.0f) rotation.y -= 360.0f;
    rotation.y += delta;
}

// Função para debugging: imprime no terminal todas informações de um modelo
// geométrico carregado de um arquivo ".obj".
// Veja: https://github.com/syoyo/tinyobjloader/blob/22883def8db9ef1f3ffb9b404318e7dd25fdbb51/loader_example.cc#L98
void PrintObjModelInfo(ObjectModel *model) {
	const tinyobj::attrib_t &attrib = model->attrib;
	const std::vector<tinyobj::shape_t> &shapes = model->shapes;
	const std::vector<tinyobj::material_t> &materials = model->materials;

	printf("# of vertices  : %d\n", (int) (attrib.vertices.size() / 3));
	printf("# of normals   : %d\n", (int) (attrib.normals.size() / 3));
	printf("# of texcoords : %d\n", (int) (attrib.texcoords.size() / 2));
	printf("# of shapes    : %d\n", (int) shapes.size());
	printf("# of materials : %d\n", (int) materials.size());

	for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
		printf("  v[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
			   static_cast<const double>(attrib.vertices[3 * v + 0]),
			   static_cast<const double>(attrib.vertices[3 * v + 1]),
			   static_cast<const double>(attrib.vertices[3 * v + 2]));
	}

	for (size_t v = 0; v < attrib.normals.size() / 3; v++) {
		printf("  n[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
			   static_cast<const double>(attrib.normals[3 * v + 0]),
			   static_cast<const double>(attrib.normals[3 * v + 1]),
			   static_cast<const double>(attrib.normals[3 * v + 2]));
	}

	for (size_t v = 0; v < attrib.texcoords.size() / 2; v++) {
		printf("  uv[%ld] = (%f, %f)\n", static_cast<long>(v),
			   static_cast<const double>(attrib.texcoords[2 * v + 0]),
			   static_cast<const double>(attrib.texcoords[2 * v + 1]));
	}

	// For each shape
	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", static_cast<long>(i),
			   shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %lu\n", static_cast<long>(i),
			   static_cast<unsigned long>(shapes[i].mesh.indices.size()));

		size_t index_offset = 0;

		assert(shapes[i].mesh.num_face_vertices.size() ==
			   shapes[i].mesh.material_ids.size());

		printf("shape[%ld].num_faces: %lu\n", static_cast<long>(i),
			   static_cast<unsigned long>(shapes[i].mesh.num_face_vertices.size()));

		// For each face
		for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++) {
			size_t fnum = shapes[i].mesh.num_face_vertices[f];

			printf("  face[%ld].fnum = %ld\n", static_cast<long>(f),
				   static_cast<unsigned long>(fnum));

			// For each vertex in the face
			for (size_t v = 0; v < fnum; v++) {
				tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];
				printf("    face[%ld].v[%ld].idx = %d/%d/%d\n", static_cast<long>(f),
					   static_cast<long>(v), idx.vertex_index, idx.normal_index,
					   idx.texcoord_index);
			}

			printf("  face[%ld].material_id = %d\n", static_cast<long>(f),
				   shapes[i].mesh.material_ids[f]);

			index_offset += fnum;
		}

		printf("shape[%ld].num_tags: %lu\n", static_cast<long>(i),
			   static_cast<unsigned long>(shapes[i].mesh.tags.size()));
		for (size_t t = 0; t < shapes[i].mesh.tags.size(); t++) {
			printf("  tag[%ld] = %s ", static_cast<long>(t),
				   shapes[i].mesh.tags[t].name.c_str());
			printf(" ints: [");
			for (size_t j = 0; j < shapes[i].mesh.tags[t].intValues.size(); ++j) {
				printf("%ld", static_cast<long>(shapes[i].mesh.tags[t].intValues[j]));
				if (j < (shapes[i].mesh.tags[t].intValues.size() - 1)) {
					printf(", ");
				}
			}
			printf("]");

			printf(" floats: [");
			for (size_t j = 0; j < shapes[i].mesh.tags[t].floatValues.size(); ++j) {
				printf("%f", static_cast<const double>(
						shapes[i].mesh.tags[t].floatValues[j]));
				if (j < (shapes[i].mesh.tags[t].floatValues.size() - 1)) {
					printf(", ");
				}
			}
			printf("]");

			printf(" strings: [");
			for (size_t j = 0; j < shapes[i].mesh.tags[t].stringValues.size(); ++j) {
				printf("%s", shapes[i].mesh.tags[t].stringValues[j].c_str());
				if (j < (shapes[i].mesh.tags[t].stringValues.size() - 1)) {
					printf(", ");
				}
			}
			printf("]");
			printf("\n");
		}
	}

	for (size_t i = 0; i < materials.size(); i++) {
		printf("material[%ld].name = %s\n", static_cast<long>(i),
			   materials[i].name.c_str());
		printf("  material.Ka = (%f, %f ,%f)\n",
			   static_cast<const double>(materials[i].ambient[0]),
			   static_cast<const double>(materials[i].ambient[1]),
			   static_cast<const double>(materials[i].ambient[2]));
		printf("  material.Kd = (%f, %f ,%f)\n",
			   static_cast<const double>(materials[i].diffuse[0]),
			   static_cast<const double>(materials[i].diffuse[1]),
			   static_cast<const double>(materials[i].diffuse[2]));
		printf("  material.Ks = (%f, %f ,%f)\n",
			   static_cast<const double>(materials[i].specular[0]),
			   static_cast<const double>(materials[i].specular[1]),
			   static_cast<const double>(materials[i].specular[2]));
		printf("  material.Tr = (%f, %f ,%f)\n",
			   static_cast<const double>(materials[i].transmittance[0]),
			   static_cast<const double>(materials[i].transmittance[1]),
			   static_cast<const double>(materials[i].transmittance[2]));
		printf("  material.Ke = (%f, %f ,%f)\n",
			   static_cast<const double>(materials[i].emission[0]),
			   static_cast<const double>(materials[i].emission[1]),
			   static_cast<const double>(materials[i].emission[2]));
		printf("  material.Ns = %f\n",
			   static_cast<const double>(materials[i].shininess));
		printf("  material.Ni = %f\n", static_cast<const double>(materials[i].ior));
		printf("  material.dissolve = %f\n",
			   static_cast<const double>(materials[i].dissolve));
		printf("  material.illum = %d\n", materials[i].illum);
		printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
		printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
		printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
		printf("  material.map_Ns = %s\n",
			   materials[i].specular_highlight_texname.c_str());
		printf("  material.map_bump = %s\n", materials[i].bump_texname.c_str());
		printf("  material.map_d = %s\n", materials[i].alpha_texname.c_str());
		printf("  material.disp = %s\n", materials[i].displacement_texname.c_str());
		printf("  <<PBR>>\n");
		printf("  material.Pr     = %f\n", materials[i].roughness);
		printf("  material.Pm     = %f\n", materials[i].metallic);
		printf("  material.Ps     = %f\n", materials[i].sheen);
		printf("  material.Pc     = %f\n", materials[i].clearcoat_thickness);
		printf("  material.Pcr    = %f\n", materials[i].clearcoat_thickness);
		printf("  material.aniso  = %f\n", materials[i].anisotropy);
		printf("  material.anisor = %f\n", materials[i].anisotropy_rotation);
		printf("  material.map_Ke = %s\n", materials[i].emissive_texname.c_str());
		printf("  material.map_Pr = %s\n", materials[i].roughness_texname.c_str());
		printf("  material.map_Pm = %s\n", materials[i].metallic_texname.c_str());
		printf("  material.map_Ps = %s\n", materials[i].sheen_texname.c_str());
		printf("  material.norm   = %s\n", materials[i].normal_texname.c_str());
		std::map<std::string, std::string>::const_iterator it(
				materials[i].unknown_parameter.begin());
		std::map<std::string, std::string>::const_iterator itEnd(
				materials[i].unknown_parameter.end());

		for (; it != itEnd; it++) {
			printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
		}
		printf("\n");
	}
}
