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
			AmplifyAbility();
			Boundary();
		}
	}

	void AmplifyAbility() {
		Vector2D_float deltaVect = transform->position - BennyTransform->position;
		float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
		//::cout << "Magnitude:" << (int)magnitude << "(200)";
		if (magnitude < radius) {
			bennyProp->SetRadius(rCal);
		}
		else {
			bennyProp->SetRadius(rOld);
		}
		//std::cout << "\tBennyRadius:" << bennyProp->GetRadius() << std::endl;
	}

	void CC::AnimationController() override {
		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if (rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }

		// Animation
		if (boxCollider2D->GetIsGround()) {	// on ground
			if (rigidBody->GetVelocityX() != 0) {
				animator->PlayState("CHERRY_RUN");
			}
			else {
				animator->PlayState("CHERRY_IDLE");
			}
		}
	}

	void SetCherry(GameObject* benny) {
		BennyTransform = &benny->GetComponent<Transform>();
		bennyProp = &benny->GetComponent<Benny>();
		rOld = bennyProp->GetRadius();
		rCal = rOld * rMultiplier;
	}

private:
	float radius = 200.0f;	// placeholder for skill range
	Transform* BennyTransform = nullptr;
	Benny* bennyProp = nullptr;
	float rMultiplier = 1.5;
	float rOld;
	float rCal; 
	bool isInRange = false;
};
