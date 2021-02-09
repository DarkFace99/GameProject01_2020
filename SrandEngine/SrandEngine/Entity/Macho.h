#pragma once

#include <vector>
#include "CC.h"

class Macho : public CC {
public:
	Macho() { SetTag(ccTag::MACHO); }
	~Macho() = default;

	bool init() {
		SetUp();
		return true;
	}

	void Update() override final {
		Input_Movement(false);
	}

private:
	Transform* targetTransform = nullptr;
};

