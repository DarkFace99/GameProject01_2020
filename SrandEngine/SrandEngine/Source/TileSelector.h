#pragma once

#include <string>

#include "GameObject.h"
#include "Component.h"
#include "SpriteRenderer.h"

class TileSelector : public Component {
private:
	float* offSetX_Ptr = nullptr;
	float* offSetY_Ptr = nullptr;

	int totalFrames_X = 1;
	int totalFrames_Y = 1;

public:
	TileSelector(int totalFrames_X, int totalFrames_Y): totalFrames_X(totalFrames_X), totalFrames_Y(totalFrames_Y){}

	void SetTile(int offsetX, int offsetY) {
		*offSetX_Ptr = (float)offsetX / totalFrames_X;
		*offSetY_Ptr = (float)offsetY / totalFrames_Y;
	}

	bool Init() override final {
		// for some reason
		offSetX_Ptr = gameObject->GetComponent<SpriteRenderer>().GetOffSetX();
		offSetY_Ptr = gameObject->GetComponent<SpriteRenderer>().GetOffSetY();
		return true;
	}
};