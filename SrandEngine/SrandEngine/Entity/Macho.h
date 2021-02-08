#pragma once

#include <vector>
#include "CC.h"

class Macho : public CC {
public:
	Macho() { SetTag(ccTag::MACHO); }
	~Macho() = default;

	bool init() {
	}

	void CheckCollision() {

	}

private:
	Transform* BennyTransform = nullptr;
};

