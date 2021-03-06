#pragma once

#include <srpch.h>
#include "ecspch.h"
#include "Source/ObjectManager.h"

using namespace Srand;

class Button : public Component 
{
private:
	BoxCollider2D* collider = nullptr;
	TileSelector* tileSelector = nullptr;
	
	int originOffsetX = 0;
	int originOffsetY = 0;
	int shiftOffsetX = 0;
	int shiftOffsetY = 0;

	bool isOffsetShifted = false;

public:
	Button() = default;
	virtual ~Button() = default;

	Button(int offsetX, int offsetY) : shiftOffsetX(offsetX), shiftOffsetY(offsetY) { isOffsetShifted = true; }

	bool Init() override final 
	{
		collider = &gameObject->GetComponent<BoxCollider2D>();
		tileSelector = &gameObject->GetComponent<TileSelector>();
		originOffsetX = tileSelector->GetOffset().x;
		originOffsetY = tileSelector->GetOffset().y;
		return true;
	}

	bool CheckCollideActivate() 
	{
		for (int i = 0; i < ObjManager::get().VectorSize(); i++) {
			if (ObjManager::get()[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION)
			{
				if (Collision::AABB(*collider, ObjManager::get()[i]->GetComponent<BoxCollider2D>())) {
					//std::cout << "Collide with button" << std::endl;
					if (isOffsetShifted) { tileSelector->SetTile(shiftOffsetX, shiftOffsetY); }
					return true;
				}
			}
		}
		if (isOffsetShifted) { tileSelector->SetTile(originOffsetX, originOffsetY); }
		return false;
	}

};
