//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#include "rendering.hpp"
#include "matrices.h"
#include "global.hpp"

Food::Food(const ObjectInstance &object, float radius) : ObjectInstance(object) {
    collider = new Physics::ColliderSphere(&position, radius);
    interact = new Physics::InteractiveCollider(
            name,
            this,
            Physics::FOOD,
            &position,
            1.5f * radius
   );
}

void Food::TryPutInTable() {
    auto coll = interact->layer->Interacting(this->interact);
    if (coll == nullptr || coll->type != Physics::TABLE) return;

    auto table = (Table*) coll->referenceObject;
    table->PutFood(this);
}

Table::Table(ObjectInstance const &object) : ObjectInstance(object) {
    // Calculte food position from bounding box
    auto center = glm::vec4(
            (triangles->bbox_min.x + triangles->bbox_max.x)/2.0f,
            triangles->bbox_max.y,
            (triangles->bbox_min.z + triangles->bbox_max.z)/2.0f,
            1.0f
    );
    center += position - glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    center.y *= scale.y * (triangles->bbox_max.y - triangles->bbox_min.y) * 2.0f;

    this->interact = new Physics::InteractiveCollider(
            name,
            this,
            Physics::TABLE,
            new glm::vec4(center),
            0.8f
   );
}

void Table::PutFood(Food* food) {
    this->food = food;
    food->position = *interact->center;
    food->position.y += ((Physics::ColliderSphere*)food->collider)->radius * 2.0f;
}

Customer::Customer(const ObjectInstance &object, Table* tableReference) : ObjectInstance(object) {
    this->tableReference = tableReference;
    this->spawnTimer = 5.0f + (float)(rand() % 30);
    this->initialRotation = rotation.y;
}

void Customer::Draw() {
    if (isBuying) {
        ObjectInstance::Draw();
    }
}

float lerp(float a, float b, float t, bool reverse) {
    if (reverse) t = 1 - t;
    return a + t * (b - a);
}

void Customer::Proc(float time, float delta) {
    isBuying = time > spawnTimer;
    if (collider != nullptr) {
        collider->active = isBuying;
    }
    if (isBuying && tableReference->food != nullptr) {
        // Eat food yum
        tableReference->food->remaining -= delta;
        // Be happy
        auto t = (float) fmod(time, 1.0f);
        rotation.y = initialRotation + lerp(-PI/2, PI/2, t, fmod(time, 2.0f) > 1.0f);
    }
}
