#pragma once
#include "raylib.h"

enum BodyType {
    RIGID_BODY,
    STATIC_BODY
};

class Entity {
public:
    float mass;
    float restitution = 0.7;
    int radius = 20;
    short shapeId;
    Vector2 position;
    Vector2 velocity;
    Vector2 forceApplied;
    BodyType bType;

    float invMass() const {
        return (bType == STATIC_BODY || mass == 0.0f) ? 
                0.0f : 1.0f / mass;
        };

    Entity(float m, Vector2 pos, BodyType b):
          mass(m), 
          position(pos), 
          velocity({0, 0}), 
          forceApplied({0, 0}), 
          shapeId(0), 
          bType(b) {}
          
    void applyForce(const Vector2& force);
    void integrate(float dt);
};
