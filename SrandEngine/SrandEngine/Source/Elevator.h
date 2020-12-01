#pragma once

#include <vector>
#include "Engine.h"
#include "Component.h"
#include "Transform.h"
#include "BoxCollider2D.h"

class Elevator : public Component 
{
private:
	Transform* transform = nullptr;
	BoxCollider2D* collider = nullptr;

	std::vector<GameObject*> connectedButtons;

public:
	Elevator() = default;
	virtual ~Elevator() = default;

	bool Init() override final 
	{
		transform = &gameObject->GetComponent<Transform>();
		collider = &gameObject->GetComponent<BoxCollider2D>();

		return true;
	}
	void Draw() override final 
	{
		
	}
	void Update() override final 
	{
		
	}

};