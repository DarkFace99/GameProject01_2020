#pragma once

#include <vector>
#include "CC.h"

//class Benny : public CC {
//public:
//	Benny() { SetTag(ccTag::BENNY); }
//	~Benny() = default;
//
//	void AbilityCheck() {	
//		for (int i = 0; i < SceneManager::get(); i++) {
//			if (SceneManager::get().objManager[i]->HasComponent<CC>()) {
//				Vector2D_float deltaVect = GetTransform()->position - SceneManager::get().objManager[i]->GetComponent<Transform>().position;
//				float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
//				if (magnitude < radius) {
//					connectList.push_back(SceneManager::get().objManager[i]);
//				}
//			}
//		}
//	}
//
//	void CC_Select(GameObject* targetCC) {
//		targetTransform = &targetCC->GetComponent<Transform>();
//	} 
//
//	bool InRange() {
//		Vector2D_float deltaVect = transform->position - targetTransform->position;
//		float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
//
//		if (magnitude < radius) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//
//	bool Init() {
//		SetTransform();
//	}
//
//private:
//	float radius = 20.0f;	// place holder 
//	std::vector<CC*>connectList;
//
//	GameObject* targetCC = nullptr;
//	Transform* targetTransform = nullptr;
//};

class Benny : public CC {
private:
	float radius = 400.0f;	// place holder 

public:
	Benny() { SetTag(ccTag::BENNY); }
	Benny(float r) { 
		radius = r;
		SetTag(ccTag::BENNY);
	}
	~Benny() = default;

	bool Init() override final {
		SetActive(true);
		SetUp();
		return true;
	}


	void Update() override final {
		if (!isOut) {
			rigidBody->Update_Gravity();
			if (isActive) { Input_Movement(true); }
			AnimationController(); // place before collision check because, it will change velocity and may result in weird animation  
			Collision_Check();
			Execute();
			Boundary();
		}
	}

	void CC::AnimationController() override {

		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if(rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }

		// Animation
		if (boxCollider2D->GetIsGround()) {	// on ground
			if (rigidBody->GetVelocityX() != 0) {
				animator->PlayState("BENNY_RUN");
			}
			else {
				animator->PlayState("BENNY_IDLE");
			}
		}
		else{ // airborne
			if (rigidBody->GetVelocityY() > 0) {
				animator->PlayState("BENNY_JUMP");
			}
			else {
				animator->PlayState("BENNY_FALL");
			}
		}
	}

	void SetRadius(float r) {
		radius = r;
	}
	float GetRadius() {
		return radius;
	}
};