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

RotatingObject::RotatingObject(const ObjectInstance &object) : ObjectInstance(object) {

}

void RotatingObject::Proc(float time, float delta) {
	if (rotation.y > 360.0f) rotation.y -= 360.0f;
	rotation.y += delta;
}

ObjectTriangles::ObjectTriangles(const char *filepath, int ID) {
	ObjectModel model(filepath);
	ComputeNormals(&model);
	BuildTriangles(&model, this);

	this->ID = ID;
}
