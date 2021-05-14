#pragma once

#include <vector>
#include "CC.h"

class Macho : public CC {
public:
	Macho() { SetTag(ccTag::MACHO); }
	~Macho() {
		targetTransform = nullptr;
		targetCollider = nullptr;
		targetRenderer = nullptr;
		targetAnimator = nullptr;
		targetRigidBody = nullptr;
		cc_CopyList.clear(); 
		isPickUp = false;
		isPickUp_Down = false;
	}

	bool Init() override final {
		SetActive(false);
		SetUp();
		return true;
	}

	void Update() override final {
		if (!isOut) {
			rigidBody->Update_Gravity();
			if (isActive) {
				Input_Movement(false);
				ThrowAbility();
			}
			//SR_SYSTEM_TRACE("Pick: {0}", isPickUp);
			if (isPickUp) { cc_Carry(); }
			AnimationController();
			Collision_Check();
			Execute();
			Boundary();
		}
	}

	void cc_Carry() {
		targetTransform->SetPosition(Vector2D_float(transform->position.x, transform->position.y + (boxCollider2D->GetHeight() / 2) + (targetCollider->GetHeight() / 2)));
		targetRenderer->SetFlip(renderer->GetFlip());
		targetRigidBody->SetVelocityY(0.0f);
		//if (targetAnimator != nullptr)targetAnimator->PlayState("IDLE");

		if (!isActive) { isPickUp = false; }
	}

	void ThrowAbility() {
		if (input.IsKeyPressed(SR_KEY_C)) { isPickUp_Down = true; }
		if(isPickUp_Down && !input.IsKeyPressed(SR_KEY_C)){
			isPickUp_Down = false;
			if (!isPickUp) {
				for (int i = 0; i < cc_CopyList.size(); i++) {
					if (!cc_CopyList[i]->HasComponent<Macho>()) {
						if (Collision::AABB(*boxCollider2D, cc_CopyList[i]->GetComponent<BoxCollider2D>())) {
							targetTransform = &cc_CopyList[i]->GetComponent<Transform>();
							targetCollider = &cc_CopyList[i]->GetComponent<BoxCollider2D>();
							targetRenderer = &cc_CopyList[i]->GetComponent<SpriteRenderer>();
							targetAnimator = &cc_CopyList[i]->GetComponent<Animator>();
							targetRigidBody = &cc_CopyList[i]->GetComponent<RigidBody>();
							isPickUp = true;
							break;
						}
					}
				}
			}
			else if (isPickUp) { // throw 
				isPickUp = false;
				if (renderer->GetFlip()) { targetRigidBody->SetVelocityX(-throwForceX); }
				else { targetRigidBody->SetVelocityX(throwForceX); }
				targetRigidBody->SetVelocityY(throwForceY);
			}
		}

		if (input.IsKeyPressed(SR_KEY_DOWN) && isPickUp) {
			isPickUp = false;
		}

	}

	void CC::AnimationController() override {
		// Flip
		if (rigidBody->GetVelocityX() > 0) { renderer->SetFlip(false); }
		else if (rigidBody->GetVelocityX() < 0) { renderer->SetFlip(true); }

		if (isActive) {
			if (boxCollider2D->GetIsGround()) {	// on ground}
				if (rigidBody->GetVelocityX() != 0) {
					animator->PlayState("MACHO_RUN");
				}
				else {
					animator->PlayState("MACHO_IDLE");
				}
			}
			else
			{
				animator->PlayState("MACHO_FALL");
			}
		}
		else if (isChosen) {
			animator->PlayState("MACHO_IDLE");
		}
		else if (isInRange) {
			animator->PlayState("MACHO_IN");
		}
		else {
			animator->PlayState("MACHO_OUT");
		}
	}

	void CopyCC_List(std::vector<GameObject*> cc_List) {
		for (int i = 0; i < cc_List.size(); i++) {
			cc_CopyList.push_back(cc_List[i]);
		}
		//SR_SYSTEM_TRACE("Macho_Copy: {0}", cc_CopyList.size());
	}

private:
	Transform* targetTransform = nullptr;
	BoxCollider2D* targetCollider = nullptr;
	SpriteRenderer* targetRenderer = nullptr;
	Animator* targetAnimator = nullptr;
	RigidBody* targetRigidBody = nullptr;
	std::vector<GameObject*> cc_CopyList;
	
	float throwForceX = 50.0f;
	float throwForceY = 1.0f;
	bool isPickUp = false;
	bool isPickUp_Down = false;
};

