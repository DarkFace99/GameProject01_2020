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
	GameObject* targetCC = nullptr;
	Transform* targetTransform = nullptr;
	float radius = 2000.0f;	// place holder 
	std::vector<CC*>connectList;

public:
	Benny() { SetTag(ccTag::BENNY); }
	Benny(float r) { 
		radius = r;
		SetTag(ccTag::BENNY);
	}
	~Benny() = default;

	bool Init() override final {
		SetUp();
		return true;
	}

	void Update() override final {
		Input_Movement(true);
		/*printf("\n\t---------------------------\n");
		printf("\t-----------Update----------\n");
		printf("\t---------------------------\n\n");*/
		Collision_Check();
		//std::cout << rigidBody->GetVelocity() << std::endl;
		Execute();
	}

};