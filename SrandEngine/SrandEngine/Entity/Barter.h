#pragma once

#include <vector>
#include "CC.h"

class Barter : public CC {
public:
	Barter() { SetTag(ccTag::BARTER); }
	~Barter() = default;

	void SwapAbility() {
		Vector2D_float temp_Pos = BennyTransform->position;
		BennyTransform->position = GetTransform()->position;
		GetTransform()->position = temp_Pos;
	}	

	bool init() {
		SetTransform();

		// function to loop through objManager to find Benny for pos
	}

private:
	Transform* BennyTransform = nullptr;

};
