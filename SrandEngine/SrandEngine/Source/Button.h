#pragma once

#include <vector>
#include "Engine.h"
#include "Component.h"
#include "Collision.h"
#include "BoxCollider2D.h"

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

	bool CheckCollideActivate() 
	{
		for (int i = 0; i < Engine::get().objManager.size(); i++) {
			if (Engine::get().objManager[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION)
			{
				if (Collision::AABB(*collider, Engine::get().objManager[i]->GetComponent<BoxCollider2D>())) {
					std::cout << "Collide with button" << std::endl;
					return true;
				}
			}
		}
		return false;
	}

};
