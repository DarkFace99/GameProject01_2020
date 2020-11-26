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

public:
	BoxCollider2D(std::string tag, float width, float height) : collisionTag(tag), width(width), height(height){}
	BoxCollider2D(float width, float height): width(width), height(height) {}

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