#include "raylib.h"
#include "world.h"
#include "entity.h"
#include "math.h"
#include <vector>

void World::addEntity(const Entity& e) {
	entities.push_back(e);
}

void World::update(float dt) {
	for (auto& e : entities) {
		e.applyForce((Vector2){gravity.x * e.mass, gravity.y * e.mass});
		e.integrate(dt);
	}
	
	for (size_t i = 0; i < entities.size(); ++i) {
		for (size_t j = i + 1; j < entities.size(); ++j) {
			auto &A = entities[i], &B = entities[j];
			
			if (A.bType == STATIC_BODY && B.bType == STATIC_BODY) continue;
			
			Vector2 normal; 
			float penetration;
			
			if (checkCollision(A, B, normal, penetration)) {
				resolveCollision(A, B, normal, penetration, dt);
			}
		}
	}
}

void World::resolveCollision(Entity& A, Entity& B, Vector2& normal, float& penetration, float dt) {
	resolveImpulse(A, B, normal);
	positionalCorrection(A, B, normal, penetration);
}

void World::draw() {
	for(auto& e : entities) {
		/**if (e.bType==STATIC_BODY){
			DrawCircleV(e.position, e.radius,(Color){82,37,70});
		}
		else{
			DrawCircleV(e.position, e.radius,(Color){247, 55, 79});
		}**/
		DrawCircleV(e.position, e.radius,(Color){166, 77, 240, 120});
		
	}
}

bool World::checkCollision(Entity& A, Entity& B, Vector2& outNormal, float& outPenetration) {

	Vector2 dist = { 
		B.position.x - A.position.x,  
		B.position.y - A.position.y
	};
	
	float dist2 = (dist.x * dist.x) + (dist.y * dist.y);
	float radiusSum = A.radius + B.radius;
	
	if (dist2 > radiusSum * radiusSum) return false;
	
	float distance = sqrt(dist2);
	
	if (distance < 0.0001f) {
		outNormal = (Vector2){0.0f, 1.0f}; 
		outPenetration = A.radius + B.radius;
		return true;
	}
   
	outNormal = (Vector2){ dist.x / distance, dist.y / distance };
	
	outPenetration = radiusSum - distance;
	return true;
}

void World::positionalCorrection(Entity& A, Entity& B, 
	Vector2& normal, float& penetration) {
	const float percent = 0.4f;  // smol = less aggresive
	const float slop = 0.01f;	// pene allocation
	
	if (penetration <= slop) return;
	
	float massSum = A.invMass() + B.invMass();
	if (massSum <= 0.0f) return;
	
	// TODO: focus on this part next time
	float correctionMagnitude = (penetration - slop) / massSum * percent;
	Vector2 correction = {
		normal.x * correctionMagnitude,
		normal.y * correctionMagnitude
	};
	
	if (A.bType != STATIC_BODY) {
		A.position.x -= correction.x * A.invMass();
		A.position.y -= correction.y * A.invMass();
	}
	
	if (B.bType != STATIC_BODY) {
		B.position.x += correction.x * B.invMass();
		B.position.y += correction.y * B.invMass();
	}
}

void World::resolveImpulse(Entity& A, Entity& B, Vector2& normal) {
	Vector2 rv = { 
		B.velocity.x - A.velocity.x, 
		B.velocity.y - A.velocity.y 
	};
 
	float velAlongNormal = rv.x * normal.x + rv.y * normal.y;
   
	if (velAlongNormal > 0) return;
 
	float e = std::min(A.restitution, B.restitution);
	float j = -(1.0f + e) * velAlongNormal;
	float massSum = A.invMass() + B.invMass();
	
	if (massSum <= 0.0f) return;
	
	j /= massSum;
	Vector2 impulse = { j * normal.x, j * normal.y };
	
	if (A.bType != STATIC_BODY) {
		A.velocity.x -= impulse.x * A.invMass();
		A.velocity.y -= impulse.y * A.invMass();
	}
	if (B.bType != STATIC_BODY) {
		B.velocity.x += impulse.x * B.invMass();
		B.velocity.y += impulse.y * B.invMass();
	}
	
	// handleFriction(A, B, normal, j); someday??
}
