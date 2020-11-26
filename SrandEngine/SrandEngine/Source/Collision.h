#pragma once

#include "BoxCollider2D.h"

class Collision{
public: 
	static bool AABB(const BoxCollider2D& colA, const BoxCollider2D& colB);
};