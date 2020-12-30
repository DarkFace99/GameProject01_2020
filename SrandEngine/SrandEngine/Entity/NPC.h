#pragma once

#include "Source/Engine.h"

#include "ecspch.h"

class NPC : public Component 
{
private:
	SpriteRenderer* spriteRenderer = nullptr;
	BoxCollider2D* collider = nullptr;
	Animator* animator = nullptr;

	bool isCollide = false;
	float fadeAlpha = 1.0f;

public:
	NPC() = default;
	virtual ~NPC() = default;

	void SetFadeAlpha(float alpha) { fadeAlpha = alpha; }
	void SetCollideFalse() {
		isCollide = false; 
		animator->PlayState("NPC_SAD");
		SetFadeAlpha(1.0f);
		spriteRenderer->SetAlpha(fadeAlpha);
	}

	bool Init() 
	{
		spriteRenderer = &gameObject->GetComponent<SpriteRenderer>();
		collider = &gameObject->GetComponent<BoxCollider2D>();
		animator = &gameObject->GetComponent<Animator>();
		return true;
	}
	void Update() 
	{
		if (!isCollide) {
			CheckCollideActivate();
		}
		else if(fadeAlpha > 0){
			fadeAlpha -= 0.01f;
			spriteRenderer->SetAlpha(fadeAlpha);
		}
		
	}

	void CheckCollideActivate() 
	{
		for (int i = 0; i < Engine::get().objManager.size(); i++) {
			if (Engine::get().objManager[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION)
			{
				if (Collision::AABB(*collider, Engine::get().objManager[i]->GetComponent<BoxCollider2D>())) {
					//std::cout << "Collide with button" << std::endl;
					animator->PlayState("NPC_HAPPY");
					isCollide = true;
					/*spriteRenderer->SetAlpha(0.0f);*/
				}
			}
		}
		//return false;
	}

};