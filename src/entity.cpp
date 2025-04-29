#include "entity.h"
#include "raylib.h"

void Entity::applyForce(const Vector2& force) {
    if (bType==STATIC_BODY) return;

    forceApplied.x += force.x;
    forceApplied.y += force.y;
}

void Entity::integrate(float dt) {
    if (bType==STATIC_BODY) return;

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

bool Entity::checkCollision(Entity& A, Entity& B, Vector2& outNormal, float& outPenetration) {
    Vector2 dist = { A.position.x - B.position.x, 
                        A.position.y - B.position.y};

    float dist2 = (dist.x*dist.x) + (dist.y*dist.y);
    float distR = A.radius + B.radius;
    if ((distR*distR)<dist2) return false; // r1+r2<d

    float d = sqrt(dist2);

    if (d>0){
        outNormal = { d.x/d, d.y/d }; // normal vec
    }
    else {
        outNormal = {1,0};
        d = distR - 1.0f; // slight displacement
    }
    outPenetration = distR - d; // penetration val
    return true;
}