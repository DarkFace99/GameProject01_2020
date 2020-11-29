#pragma once

#include <string>

#include "GameObject.h"
#include "Component.h"

class BoxCollider2D : public Component{
private:
	friend class Collision;
	float width, height;
	std::string collisionTag = "";
	Transform* transform = nullptr;

	bool allowOverlap = false;
	bool movable = false;

public:
	BoxCollider2D(std::string tag, float width, float height, bool overlap = false, bool movable = false)
		: collisionTag(tag), width(width), height(height), allowOverlap(overlap), movable(movable){}
	BoxCollider2D(float width, float height, bool overlap = false, bool movable = false)
		: width(width), height(height), allowOverlap(overlap), movable(movable){}

	std::string GetTag() { return collisionTag; }

	bool Init() override final {
		return true;
	}

	void Update() override final {
		transform = &gameObject->GetComponent<Transform>();
	}

	void Draw() override final {
	
	}
};