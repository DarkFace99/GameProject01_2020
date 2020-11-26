#include "Collision.h"

bool Collision::AABB(const BoxCollider2D& colA, const BoxCollider2D& colB) {
	return	(colA.transform->position.x + colA.width >= colB.transform->position.x) &&
			(colB.transform->position.x + colB.width >= colA.transform->position.x) &&
			(colA.transform->position.y + colA.height >= colB.transform->position.y) &&
			(colB.transform->position.y + colB.height >= colA.transform->position.y);
}