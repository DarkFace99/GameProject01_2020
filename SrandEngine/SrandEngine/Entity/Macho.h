#pragma once

#include <vector>
#include "CC.h"

class Macho : public CC {
public:
	Macho() { SetTag(ccTag::MACHO); }
	~Macho() = default;

	bool Init() override final {
		SetActive(false);
		SetUp();
		return true;
	}

	void Update() override final {
		rigidBody->Update_Gravity();
		if (isActive) { Input_Movement(false); }
		AnimationController();
		Collision_Check();
		Execute();
	}

	void CC::AnimationController() override {
		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if (rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }
	}

private:
	Transform* targetTransform = nullptr;
};

