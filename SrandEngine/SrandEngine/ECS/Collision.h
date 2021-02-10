#pragma once

#include "BoxCollider2D.h"
#include "RigidBody.h"
#include "Source/Engine.h" // for objManager

class Collision{
public: 
	static bool CC_AABB(GameObject& objA, GameObject& objB); // for CC
	static void CC_Collision_Push(RigidBody& rigA, BoxCollider2D& colA, BoxCollider2D& colB);
	static bool IsOnGround(GameObject& objA, GameObject& objB);
};