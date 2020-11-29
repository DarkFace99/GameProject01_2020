#pragma once

#include "BoxCollider2D.h"

class Collision{
public: 
	static bool AABB(BoxCollider2D& colA,BoxCollider2D& colB);
	static void CollisionPush(BoxCollider2D& colA, BoxCollider2D& colB);
};