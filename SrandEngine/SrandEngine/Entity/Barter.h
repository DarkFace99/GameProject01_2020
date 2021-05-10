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

		audioController.Play("Barter_swap");
	}	

	bool Init() override final {
		SetActive(false);
		SetUp();
		return true;
	}

	void Update() override final {
		if (!isOut) {
			if (isActive) {
				SwapAbility();
				SetActive(false);
			}
			rigidBody->Update_Gravity();
			AnimationController();
			Collision_Check();
			Execute();
			Boundary();
		}
	}

	void CC::AnimationController() override {
		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if (rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }

		if (isActive) {
			if (boxCollider2D->GetIsGround()) {	// on ground
				animator->PlayState("BARTER_IDLE");
			}
		}
		else if (isChosen) {
			animator->PlayState("BARTER_IDLE");
		}
		else {
			animator->PlayState("BARTER_OUT");
		}
	}

	void SetBarter(GameObject* benny) {
		BennyTransform = &benny->GetComponent<Transform>();
		BennyCollider = &benny->GetComponent<BoxCollider2D>();
	}

	

private:
	Transform* BennyTransform = nullptr;
	BoxCollider2D* BennyCollider = nullptr;
};
