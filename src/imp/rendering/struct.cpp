//
// Guilherme Wagner Correa
// Cartão: 00303992
//

#include "rendering.hpp"
#include <stdexcept>

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
