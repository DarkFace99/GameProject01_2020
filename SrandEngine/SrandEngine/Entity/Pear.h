#pragma once

#include "CC.h"

class Pear : public CC {
public:
	Pear() { SetTag(ccTag::PEAR); }
	~Pear() = default;

	// just set isActive to both Benny & Pear
	// wait for input section

	bool Init() override final {
		SetActive(false);
		SetUp();
		return true;
	}

	void Update() override final {
		rigidBody->Update_Gravity();
		if (isActive) { Input_Movement(true); }
		AnimationController();
		Collision_Check();
		Execute();
	}

	void CC::AnimationController() override {
		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if (rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }

		// Animation
		if (boxCollider2D->GetIsGround()) {	// on ground
			if (rigidBody->GetVelocityX() != 0) {
				animator->PlayState("PEAR_RUN");
			}
			else {
				animator->PlayState("PEAR_IDLE");
			}
		}
	}
}; 
