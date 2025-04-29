#pragma once
#include "raylib.h"

enum BodyType {
    RIGID_BODY,
    STATIC_BODY
};

class Entity {
public:
    float mass;
    short shapeId;
    Vector2 position;
    Vector2 velocity;
    Vector2 forceApplied;
    BodyType bType;

    Entity(float m, Vector2 pos, BodyType b)
        : mass(m), 
          position(pos), 
          velocity({0, 0}), 
          forceApplied({0, 0}), 
          shapeId(0), 
          bType(b) {}
          
    void applyForce(const Vector2& force);
    void integrate(float dt);
};
