#pragma once

#include "Engine.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "Collision.h"
#include "BoxCollider2D.h"

class NPC : public Component 
{
private:
	SpriteRenderer* spriteRenderer = nullptr;
	BoxCollider2D* collider = nullptr;

public:
	NPC() = default;
	virtual ~NPC() = default;

	bool Init() 
	{
		spriteRenderer = &gameObject->GetComponent<SpriteRenderer>();
		collider = &gameObject->GetComponent<BoxCollider2D>();
		return true;
	}
	void Update() 
	{
		CheckCollideActivate();
	}

	void CheckCollideActivate() 
	{
		for (int i = 0; i < Engine::get().objManager.size(); i++) {
			if (Engine::get().objManager[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION)
			{
				if (Collision::AABB(*collider, Engine::get().objManager[i]->GetComponent<BoxCollider2D>())) {
					//std::cout << "Collide with button" << std::endl;
					spriteRenderer->SetAlpha(0.0f);
				}
			}
		}
		//return false;
	}

};