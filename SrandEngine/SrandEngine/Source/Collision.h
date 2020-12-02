#pragma once

#include "BoxCollider2D.h"
#include "Engine.h" // for objManager

class Collision{
public: 
	static bool AABB(BoxCollider2D& colA,BoxCollider2D& colB);
	static void CollisionPush(BoxCollider2D& colA, BoxCollider2D& colB);
	static bool IsOnGround(GameObject& objA, GameObject& objB);
};