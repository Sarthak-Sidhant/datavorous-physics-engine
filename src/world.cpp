#include "raylib.h"
#include "world.h"
#include "entity.h"
#include <vector>

void World::addEntity(const Entity& e) {
		entities.push_back(e);
}

void World::update(float dt) {
	for (auto& e : entities) {
		e.applyForce((Vector2)
			{gravity.x * e.mass, gravity.y * e.mass});
		e.integrate(dt);
	}
}

void World::draw() {
	for(auto& e : entities) {
		DrawCircleV(e.position, 20, (Color){104, 153, 237, 180});
	}
}