#include "entity.h"
#include "raylib.h"

void Entity::applyForce(const Vector2& force) {
    forceApplied.x += force.x;
    forceApplied.y += force.y;
}

void Entity::integrate(float dt) {
    Vector2 acceleration = {0,0};
    acceleration.x = forceApplied.x / mass;
    acceleration.y = forceApplied.y / mass;

    // TODO: check if it's called semi implicit euler

    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    forceApplied = {0,0};
}