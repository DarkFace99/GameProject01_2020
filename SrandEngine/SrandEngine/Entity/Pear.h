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
		if (!isOut) {
			rigidBody->Update_Gravity();
			if (isActive) { Input_Movement(true); }
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
				if (rigidBody->GetVelocityX() != 0) {
					animator->PlayState("PEAR_RUN");
				}
				else {
					animator->PlayState("PEAR_IDLE");
				}
			}
			else { // airborne
				if (rigidBody->GetVelocityY() > 0) {
					animator->PlayState("PEAR_JUMP");
				}
				else {
					animator->PlayState("PEAR_FALL");
				}
			}
		}
		else if (isChosen) {
			animator->PlayState("PEAR_IDLE");
		}
		else if (isInRange) {
			animator->PlayState("PEAR_IN");
		}
		else {
			animator->PlayState("PEAR_OUT");
		}
	}
}; 
