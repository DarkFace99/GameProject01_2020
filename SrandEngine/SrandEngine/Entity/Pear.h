#pragma once

#include <vector>
#include "CC.h"

class Pear : public CC {
public:
	Pear() { SetTag(ccTag::PEAR); }
	~Pear() = default;

	// just set isActive to both Benny & Pear
	// wait for input section

	bool init() {
		SetTransform();
	}
}; 
