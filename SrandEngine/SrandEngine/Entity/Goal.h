#pragma once
#include <srpch.h>
#include "ecspch.h"

//using namespace Srand;

class Goal : public Component 
{
private:
	BoxCollider2D* collider = nullptr;
	TileSelector* tileSelector = nullptr;
	SpriteRenderer* renderer = nullptr;
	
	int originOffsetX = 0;
	int originOffsetY = 0;
	int shiftOffsetX = 0;
	int shiftOffsetY = 0;

	bool isOffsetShifted = false;

public:
	Goal() = default;
	virtual ~Goal() = default;

	Goal(int offsetX, int offsetY) : shiftOffsetX(offsetX), shiftOffsetY(offsetY) { isOffsetShifted = true; }

	bool Init() override final 
	{
		collider = &gameObject->GetComponent<BoxCollider2D>();
		tileSelector = &gameObject->GetComponent<TileSelector>();
		renderer = &gameObject->GetComponent<SpriteRenderer>();
		originOffsetX = tileSelector->GetOffset().x;
		originOffsetY = tileSelector->GetOffset().y;

		return true;
	}

	void CheckCCActivate() { renderer->SetAlpha(1.0f); }

	void CheckBennyActive(){ tileSelector->SetTile(shiftOffsetX,shiftOffsetY); }

};
