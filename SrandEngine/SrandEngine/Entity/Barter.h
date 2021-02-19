#pragma once

#include "CC.h"

class Barter : public CC {
public:
	Barter() { SetTag(ccTag::BARTER); }
	~Barter() = default;

	void SwapAbility() {
		Vector2D_float temp = BennyTransform->position;
		BennyTransform->SetPosition(transform->position);
		transform->SetPosition(temp);
	}	

	bool Init() {
		SetUp();
		SetActive(true);
	}

	void Update() override final {
		rigidBody->Update_Gravity();
		Collision_Check();
		Execute();
	}

private:
	Transform* BennyTransform = nullptr;
};
