//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "rendering.hpp"
#include <stdexcept>

ObjectModel::ObjectModel(const char *filename, const char *basepath, bool triangulate) {
	printf("Carregando modelo \"%s\"... ", filename);

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);

	if (!err.empty()) fprintf(stderr, "\n%s\n", err.c_str());

	if (!ret) throw std::runtime_error("Erro ao carregar modelo.");

	printf("OK.\n");
}

SceneObject::SceneObject(const SceneObject &object) {
	name = object.name;
	position = object.position;
	rotation = object.rotation;
	triangles = object.triangles;
}

SceneObject::SceneObject(const char* name, glm::vec3 position, glm::vec3 rotation, RenderObject* triangles) {
	this->name = name;
	this->position = position;
	this->rotation = rotation;
	this->triangles = triangles;
}

void SceneObject::Proc(float time, float delta) {

}

RotatingObject::RotatingObject(const SceneObject &object) : SceneObject(object) {

}

void RotatingObject::Proc(float time, float delta) {
	if (rotation.y > 360.0f) rotation.y -= 360.0f;
	rotation.y += delta;
}

RenderObject::RenderObject(const char *filepath, int ID) {
	ObjectModel model(filepath);
	ComputeNormals(&model);
	BuildTriangles(&model, this);

	this->ID = ID;
}
