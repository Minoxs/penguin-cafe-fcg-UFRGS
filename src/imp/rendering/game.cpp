//
// Guilherme Wagner Correa
// Cartão: 00303992
//
#include <algorithm>
#include "rendering.hpp"
#include "matrices.h"
#include "global.hpp"

InteractiveObject::InteractiveObject(const ObjectInstance &object) : ObjectInstance(object) {

}

int f_FoodID = 0;

Food::Food(const ObjectInstance &object, float radius, float value) : InteractiveObject(object) {
    name.append(std::to_string(f_FoodID));
    f_FoodID += 1;
    collider = new Physics::ColliderSphere(
            &position,
            radius
    );
    interact = new Physics::InteractiveCollider(
            name,
            this,
            Physics::FOOD,
            &position,
            radius
    );
    foodValue = value;
}

bool Food::TryPutInTable() {
    auto coll = interact->layer->Interacting(this->interact, Physics::TABLE);
    if (coll == nullptr) return false;

    auto table = (Table*) coll->referenceObject;
    return table->PutFood(this);
}

Food::~Food() {
    if (sceneReference != nullptr) {
        sceneReference->foodCount -= 1;
        sceneReference->virtualScene.erase(name);
    }
    delete collider;
    delete interact;
}

Table::Table(ObjectInstance const &object) : InteractiveObject(object) {
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

bool Table::PutFood(Food* food) {
    if (this->food != nullptr) return false;

    this->food = food;
    food->position = *interact->center;
    food->position.y += ((Physics::ColliderSphere*)food->collider)->radius * 2.0f;

    food->interact->active = false;
    interact->active = false;
    return true;
}

void Table::Proc(float time, float delta) {
    if (food != nullptr && food->remaining <= 0.0f) {
        delete food;
        food = nullptr;
        interact->active = true;
    }
}

Customer::Customer(const ObjectInstance &object, Table* tableReference) : InteractiveObject(object) {
    this->tableReference = tableReference;
    this->spawnTimer = 0.0f;//5.0f + (float)(rand() % 30); // TODO UNDO THIS
    this->initialRotation = rotation.y;
    interact = new Physics::InteractiveCollider(
            name,
            this,
            Physics::CUSTOMER,
            &position,
            1.0f
    );
    interact->active = false;
    // TODO BE SMART SOME OTHER DAY
    customerFaceDirection =
            (90.0f * PI / 180.0f == rotation.y) ?
            glm::vec4(0.0f, 0.0f, -1.0f, 0.0f) :
            glm::vec4(0.0f, 0.0f, +1.0f, 0.0f);
}

float Customer::GetMoney() {
    if (!waitingForPayment) return 0;

    auto money = amountEaten / 100.0f;
    isBuying = false;
    waitingForPayment = false;
    interact->active = false;
    spawnTimer += Customer::SpawnDelay + (float)(rand() % 30);
    amountEaten = 0.0f;
    rotation.y = initialRotation;
    return money;
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
    collider->active = isBuying;

    if (!isBuying) return;
    spawnTimer = time;

    if (waitingForPayment) {
        // Look at player
        auto player = sceneReference->player;

        // Gambiarra to make customer face player
        auto playerDirection = (player->position - position)/norm(player->position - position);
        const auto upVector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
        auto side = crossproduct(upVector, customerFaceDirection);
        auto rotationNeeded = dotproduct(playerDirection, customerFaceDirection);
        auto left = dotproduct(playerDirection, side) > 0.0f;
        auto invert = (left) ? -1.0f : 1.0f;
        rotation.y = initialRotation + (rotationNeeded - 1) * PI / 2 * invert;
        return;
    }

    if (tableReference->food != nullptr) {
        // Eat food yum
        auto foodCap = std::clamp(delta * 2.5f, 0.0f, tableReference->food->remaining);
        amountEaten += foodCap * tableReference->food->foodValue;
        tableReference->food->remaining -= foodCap;
        // Be happy
        auto t = (float) fmod(time, 1.0f);
        rotation.y = initialRotation + lerp(-PI/2, PI/2, t, fmod(time, 2.0f) > 1.0f);
    } else if (amountEaten > 0.0f) {
        // Done eating
        // Wait for player to get your money
        interact->active = true;
        waitingForPayment = true;
    }
}
