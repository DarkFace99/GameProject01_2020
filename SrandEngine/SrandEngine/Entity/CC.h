#pragma once

#include "Source/LevelManager.h"
#include "Source/WindowsInput.h"
#include "ecspch.h"
#include "srpch.h"
#include "ECS/Collision.h"

#include "Source/Audio.h"

class CC : public Component	// base class for CC
{
public:						// Not sure if this the best way to implement it. 
	enum class ccTag {			// If you know a better, feel free to let me know.
		DEFAULT = 0,
		BENNY,
		MACHO,
		CHERRY,
		PEAR,
		BARTER,
		UI_Box
	};


	CC() = default;
	virtual ~CC() = default;

	inline void SetTag(ccTag cctag) { CC:tag = cctag; }	// Not use directly, it will be called in the constructor of each derived CC class.												
	ccTag GetTag() { return tag; }	// to check CC type.


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

		if (input.IsKeyPressed(SR_KEY_UP) && canJump && boxCollider2D->GetIsGround()) {
			rigidBody->SetVelocityY(10.0f);
			audioController.Play("Char_jump");
		}

		if (input.IsKeyPressed(SR_KEY_LEFT) && input.IsKeyPressed(SR_KEY_RIGHT)) {} // do nothing
		else if (input.IsKeyPressed(SR_KEY_LEFT)) {
			rigidBody->SetVelocityX(-3.0f);
		}
		else if (input.IsKeyPressed(SR_KEY_RIGHT)) {
			rigidBody->SetVelocityX(3.0f);
		}
		else if (input.IsKeyPressed(SR_KEY_DOWN)) {
		// do nothing
		}

		//SR_TRACE("VelX: {0}", rigidBody->GetVelocityX());

	}
	void Collision_Check() {
		boxCollider2D->SetIsGround(false);	// reset 
		for (int i = 0; i < objManager.VectorSize(); i++) {
			if (gameObject == objManager[i]) { continue; }
			Collision::CC_AABB(*gameObject, *objManager[i]);
		}
		/*std::cout << "\nisGround:" << boxCollider2D->GetIsGround() << std::endl;
		std::cout << "\n**************** END LOOP ****************\n\n";*/
	}
	void Execute() {
		transform->Translate(rigidBody->GetVelocity());
	}

	void Boundary() {
		if (transform->position.x < -x_bound) { transform->SetPosition(Vector2D_float(-x_bound, transform->position.y)); }
		if (transform->position.x > x_bound) { transform->SetPosition(Vector2D_float(x_bound, transform->position.y)); }
		if (transform->position.y < -y_bound) { transform->SetPosition(Vector2D_float(transform->position.x, -y_bound)); }
		if (transform->position.y > y_bound) { transform->SetPosition(Vector2D_float(transform->position.x, y_bound)); }
	}

	void OutOfLevel() {
		isOut = true;
		renderer->SetAlpha(0.0f);
	}
	
	void SetIsOut(bool state) { isOut = state; }
	bool GetIsOut() { return isOut; }
	bool GetIsActive() { return isActive; }

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
	AudioController& audioController = AudioController::get();

	bool isOut = false;

	// screen boundary
	float x_bound = 630.0f;
	float y_bound = 360.0f;
};