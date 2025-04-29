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
};
