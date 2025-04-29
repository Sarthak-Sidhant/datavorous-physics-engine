#pragma once
#include "raylib.h"
class Entity {
public:
    float mass;
    short shapeId;
    Vector2 position;
    Vector2 velocity;
    Vector2 forceApplied;

    Entity(float m, Vector2 pos)
        : mass(m), 
          position(pos), 
          velocity({0, 0}), 
          forceApplied({0, 0}), 
          shapeId(0) {}
          
    void applyForce(const Vector2& force);
    void integrate(float dt);
};
