#pragma once

#include "Source/LevelManager.h"
#include "Source/WindowsInput.h"
#include "ecspch.h"
#include "srpch.h"

class CC : public Component	// base class for CC
{
public:						// Not sure if this the best way to implement it. 
	enum class ccTag {			// If you know a better, feel free to let me know.
		DEFAULT = 0,
		BENNY,
		MACHO,
		CHERRY,
		PEAR,
		BARTER
	};

	CC() = default;
	virtual ~CC() = default;

	inline void SetTag(ccTag cctag) { CC:tag = cctag; }	// Not use directly, it will be called in the constructor of each derived CC class.												
	//ccTag GetTag() { return tag; }	// to check CC type.

	void SetUp() { 
		transform = &gameObject->GetComponent<Transform>(); 
		rigidBody = &gameObject->GetComponent<RigidBody>();
		boxCollider2D = &gameObject->GetComponent<BoxCollider2D>();
	}
	//Transform* GetTransform(){ return transform; }

	void SetActive(bool state) { isActive = state; }

	void Input_Movement(bool canJump) {	// basic movement
		
		if (boxCollider2D->GetIsGround()) {
			rigidBody->SetVelocityY(0.0f);
			isOnGround = true;
		}
		else { isOnGround = false; }

		if(input.IsKeyPressed(SR_KEY_UP) && canJump) {
			//printf("jump\n");
			rigidBody->SetVelocityY(5.0f);
		}
		if (input.IsKeyPressed(SR_KEY_LEFT) && input.IsKeyPressed(SR_KEY_RIGHT)) {
			// stay still
		}
		else if (input.IsKeyPressed(SR_KEY_LEFT)) {
			//printf("left\n");
			rigidBody->SetVelocityX(-5.0f);
		}else if (input.IsKeyPressed(SR_KEY_RIGHT)) {
			//printf("right\n");
			rigidBody->SetVelocityX(5.0f);
		}
		std::cout << rigidBody->GetVelocity() << std::endl;

		transform->Translate(rigidBody->GetVelocity());	// translate after calculate every thing
	}

protected:
	Transform* transform = nullptr;
	RigidBody* rigidBody = nullptr;
	BoxCollider2D* boxCollider2D = nullptr;
	bool isActive = false;
	ccTag tag = ccTag::DEFAULT;
	WindowsInput input;
	ObjManager& objManager = ObjManager::get();
	bool isOnGround = false;
};