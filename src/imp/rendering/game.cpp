//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#include "rendering.hpp"
#include "rendering/game.hpp"

Food::Food(const ObjectInstance &object, float radius) : ObjectInstance(object) {
    collider = new Physics::ColliderSphere(&position, radius);
    interact = new Physics::InteractiveCollider(name, this, Physics::FOOD, &position, 1.5f * radius);
}

Table::Table(const ObjectInstance &object, glm::vec4 foodPosition) : ObjectInstance(object) {
    this->foodPosition = foodPosition;
}

Customer::Customer(const ObjectInstance &object, const char *tableName) : ObjectInstance(object) {
    this->tableName = tableName;
    this->spawnTimer = 5.0f + (float)(rand() % 30);
}

void Customer::Draw() {
    if (isBuying) {
        ObjectInstance::Draw();
    }
}

void Customer::Proc(float time, float delta) {
    // TODO IMPLEMENT CUSTOMER LOGIC
    isBuying = time > spawnTimer;
    if (collider != nullptr) {
        collider->active = isBuying;
    }
}
