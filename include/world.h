#pragma once
#include "raylib.h"
#include "entity.h"
#include <vector>
class World {
public:
	Vector2 gravity;
	std::vector<Entity> entities;

	World(Vector2 g) : gravity(g) {}

	void addEntity(const Entity& e);
	void update(float dt);
	void draw();
	bool checkCollision(Entity& A, Entity& B,
        Vector2& outNormal, float& outPenetration);
    void positionalCorrection(Entity& A, Entity& B, 
        Vector2& outNormal, float& outPenetration);
    void resolveCollision(Entity& A, Entity& B, Vector2& normal, float& penetration, float dt);
    void resolveImpulse(Entity& A, Entity& B, Vector2& normal);
    void handleFriction(Entity& A, Entity& B, Vector2& normal, float impulse);
};
