#pragma once

#include "Source/LevelManager.h"
#include "Source/WindowsInput.h"
#include "ecspch.h"
#include "srpch.h"
#include "ECS/Collision.h"

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
		renderer = &gameObject->GetComponent<SpriteRenderer>();
		animator = &gameObject->GetComponent<Animator>();
	}
	//Transform* GetTransform(){ return transform; }

	void SetActive(bool state) { isActive = state; }

	void Input_Movement(bool canJump) {	// basic movement

		
		if (boxCollider2D->GetIsGround()) { rigidBody->SetVelocityY(0.0f); }
		
		if(input.IsKeyPressed(SR_KEY_UP) && canJump && boxCollider2D->GetIsGround()) {
			rigidBody->SetVelocityY(8.0f);
		}

		if (input.IsKeyPressed(SR_KEY_LEFT) && input.IsKeyPressed(SR_KEY_RIGHT)) {} // do nothing
		else if (input.IsKeyPressed(SR_KEY_LEFT)) {
			rigidBody->SetVelocityX(-2.0f);
		}else if (input.IsKeyPressed(SR_KEY_RIGHT)) {
			rigidBody->SetVelocityX(2.0f);
		}	
	}
	void Collision_Check() { 
		boxCollider2D->SetIsGround(false);	// reset 
		for (int i = 0; i < objManager.VectorSize(); i++) {
			if (gameObject == objManager[i]) { continue; }
			Collision::CC_AABB(*gameObject,*objManager[i]);
		}
		/*std::cout << "\nisGround:" << boxCollider2D->GetIsGround() << std::endl;
		std::cout << "\n**************** END LOOP ****************\n\n";*/
	}
	void Execute() { 
		transform->Translate(rigidBody->GetVelocity());
	}

	virtual void AnimationController() = 0;

protected:
	Transform* transform = nullptr;
	RigidBody* rigidBody = nullptr;
	BoxCollider2D* boxCollider2D = nullptr;
	Animator* animator = nullptr;
	SpriteRenderer* renderer = nullptr;

	bool isActive = false;
	ccTag tag = ccTag::DEFAULT;
	WindowsInput input;
	ObjManager& objManager = ObjManager::get();
};