#pragma once

#include <vector>
#include "CC.h"

class Cherry : public CC {
public:
	Cherry() { SetTag(ccTag::CHERRY); }
	~Cherry() = default;

	bool init() {
		SetTransform();
	}

	void AmplifyAbility() {
		
	}

private:
	Transform* BennyTransform = nullptr;
};
