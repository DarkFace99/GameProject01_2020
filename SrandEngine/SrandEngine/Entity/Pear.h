#pragma once

#include "CC.h"

class Pear : public CC {
public:
	Pear() { SetTag(ccTag::PEAR); }
	~Pear() = default;

	// just set isActive to both Benny & Pear
	// wait for input section

	bool Init() override final {
		SetActive(true);
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
	}
}; 
