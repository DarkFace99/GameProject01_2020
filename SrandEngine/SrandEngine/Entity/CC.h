#pragma once

#include "Source/ObjectManager.h"
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

	void SetTransform() { transform = &gameObject->GetComponent<Transform>(); }
	//Transform* GetTransform(){ return transform; }

	void SetActive(bool state) { isActive = state; }

	void Input_Movement(bool isJump) {	// basic movement
		if(input.IsKeyPressed(SR_KEY_UP) && isJump) {
			printf("jump\n");
		}
		if (input.IsKeyPressed(SR_KEY_LEFT) && isJump) {
			printf("left\n");
			transform->Translate(Vector2D_float(-5.0f,0.0f));
		}
		if (input.IsKeyPressed(SR_KEY_RIGHT) && isJump) {
			printf("right\n");
			transform->Translate(Vector2D_float(5.0f, 0.0f));
		}
	}

protected:
	Transform* transform = nullptr;
	bool isActive = false;
	ccTag tag = ccTag::DEFAULT;
	WindowsInput input;
	ObjManager& objManager = ObjManager::get();
};