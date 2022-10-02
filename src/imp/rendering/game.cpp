//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#include "rendering.hpp"

Table::Table(const ObjectInstance &object, glm::vec4 foodPosition) : ObjectInstance(object) {
    this->foodPosition = foodPosition;
}

Customer::Customer(const ObjectInstance &object, const char *tableName) : ObjectInstance(object) {
    this->tableName = tableName;
}

void Customer::Draw() {
    if (isBuying) {
        ObjectInstance::Draw();
    }
}

Food::Food(const ObjectInstance &object, float radius) : ObjectInstance(object) {
    collider = new Physics::ColliderSphere(&position, radius);
    interact = new Physics::InteractiveCollider(name, Physics::FOOD, &position, radius);
}
