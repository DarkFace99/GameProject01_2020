#pragma once

#include "CC.h"

class Barter : public CC {
public:
	Barter() { SetTag(ccTag::BARTER); }
	~Barter() = default;

	void SwapAbility() {
		boxCollider2D->SetOverlap(true);
		BennyCollider->SetOverlap(true);
		Vector2D_float temp = BennyTransform->position;
		BennyTransform->SetPosition(transform->position);
		transform->SetPosition(temp);
		boxCollider2D->SetOverlap(false);
		BennyCollider->SetOverlap(false);
	}	

	bool Init() override final {
		SetActive(false);
		SetUp();
		return true;
	}

	void Update() override final {
		if (isActive) { 
			SwapAbility(); 
			SetActive(false);
		}
		rigidBody->Update_Gravity();
		Collision_Check();
		Execute();
	}

	void SetBarter(GameObject* benny) {
		BennyTransform = &benny->GetComponent<Transform>();
		BennyCollider = &benny->GetComponent<BoxCollider2D>();
	}

	void CC::AnimationController() override {}

private:
	Transform* BennyTransform = nullptr;
	BoxCollider2D* BennyCollider = nullptr;
};
