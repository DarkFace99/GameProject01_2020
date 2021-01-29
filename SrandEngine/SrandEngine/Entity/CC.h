#pragma once

#include "Source/SceneManager.h"	// to access objmanager
#include "ecspch.h"

class CC : public Component	// base class for CC
{
public:						// Not sure if this the best way to implement it. 
	enum ccTag {			// If you know a better, feel free to let me know.
		DEFAULT = 0,
		BENNY,
		MACHO,
		CHERRY,
		PAIR,
		BARTER
	};

	CC() = default;
	virtual ~CC() = default;

	void SetTag(ccTag cctag) { CC:tag = cctag; }	// Not use directly, it will be called in the
													// constructor of each derived CC class.
	ccTag GetTag() { return tag; }	// to check CC type.

	void SetTransform() { transform = &gameObject->GetComponent<Transform>(); }
	Transform GetTransform(){ return *transform; }

private:
	Transform* transform = nullptr;
	ccTag tag = ccTag::DEFAULT;

	bool inControl = false;
	Transform* targetTransform = nullptr;
};