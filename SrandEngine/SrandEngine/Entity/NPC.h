#pragma once

#include "Source/SceneManager.h"

#include "ecspch.h"
#include "Source/LevelManager.h"

using namespace Srand;

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
		LevelManager::get().AddNPC();
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
		for (int i = 0; i < ObjManager::get().VectorSize() - 1; i++) {
			if (ObjManager::get()[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION)
			{
				if (Collision::AABB(*collider, ObjManager::get()[i]->GetComponent<BoxCollider2D>())) {
					//std::cout << "Collide with button" << std::endl;
					animator->PlayState("NPC_HAPPY");
					AudioController::get().Play("NPC_rescue");
					isCollide = true;
					LevelManager::get().NpcFound();
					/*spriteRenderer->SetAlpha(0.0f);*/
				}
			}
		}
		//return false;
	}

};