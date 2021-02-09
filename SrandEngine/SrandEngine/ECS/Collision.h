#pragma once

#include "BoxCollider2D.h"
#include "Source/Engine.h" // for objManager

class Collision{
public: 
	static bool AABB(GameObject& obj);
	static void CollisionPush(GameObject& obj);
	static bool IsOnGround(GameObject& obj);
};