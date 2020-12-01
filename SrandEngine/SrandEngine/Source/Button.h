#pragma once

#include <vector>
#include "Component.h"
#include "Collision.h"
#include "BoxCollider2D.h"
#include "Door.h"

class Button : public Component 
{
private:
	BoxCollider2D* collider = nullptr;
	
public:
	Button() = default;
	virtual ~Button() = default;

	bool Init() override final 
	{
		collider = &gameObject->GetComponent<BoxCollider2D>();
		return true;
	}

	void CheckCollideActivate(GameObject* player) 
	{
		if (Collision::AABB(player->GetComponent<BoxCollider2D>(), gameObject->GetComponent<BoxCollider2D>())) 
		{
			std::cout << "Collide with button" << std::endl;
		}
	}

};
