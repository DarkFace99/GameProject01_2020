#pragma once

#include "CC.h"

class Cherry : public CC {
public:
	Cherry() { SetTag(ccTag::CHERRY); }
	Cherry(float r) {
		radius = r;
		SetTag(ccTag::CHERRY);
	}
	~Cherry() = default;

	bool init() {
	}

	void AmplifyAbility() {
		Vector2D_float deltaVect = transform->position - BennyTransform->position;
		float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
		if (magnitude < radius) {
			rCal = bennyProp->GetRadius() * rMultiplier;
			bennyProp->SetRadius(rCal);
		}
		else {
			bennyProp->SetRadius(rOld);
		}
	}

	void CC::AnimationController() override {
		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if (rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }
	}

private:
	float radius = 200.0f;	// placeholder for skill range
	Transform* BennyTransform = nullptr;
	Benny* bennyProp = nullptr;
	float rMultiplier = 1.5;
	float rOld;
	float rCal; 
};
