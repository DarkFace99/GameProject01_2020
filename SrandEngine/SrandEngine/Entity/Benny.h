#pragma once

#include <vector>
#include "CC.h"

class Benny : public CC {
public:
	Benny() { SetTag(ccTag::BENNY); }
	~Benny() = default;

	void AbilityCheck() {	
		for (int i = 0; i < SceneManager::get().objManager.size(); i++) {
			if (SceneManager::get().objManager[i]->HasComponent<CC>()) {
				Vector2D_float deltaVect = GetTransform()->position - SceneManager::get().objManager[i]->GetComponent<Transform>().position;
				float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
				if (magnitude < radius) {
					connectList.push_back(SceneManager::get().objManager[i]);
				}
			}
		}
	}

	void CC_Select(GameObject* targetCC) {
		targetTransform = &targetCC->GetComponent<Transform>();
	} 

	bool InRange() {
		Vector2D_float deltaVect = GetTransform().position - targetTransform->position;
		float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));

		if (magnitude < radius) {
			return true;
		}
		else {
			return false;
		}
	}

	bool init() {
		SetTransform();
	}

private:
	float radius = 20.0f;	// place holder 
	std::vector<GameObject*>connectList;

	GameObject* targetCC = nullptr;
	Transform* targetTransform = nullptr;
};