//#include "Collision.h"
//
//bool Collision::AABB(BoxCollider2D& colA, BoxCollider2D& colB) {
//	bool isCollide = (colA.modifyPosition.x + (colA.width / 2.0f) +  > colB.modifyPosition.x - (colB.width / 2.0f)) &&
//					 (colB.modifyPosition.x + (colB.width / 2.0f) > colA.modifyPosition.x - (colA.width / 2.0f)) &&
//					 (colA.modifyPosition.y + (colA.height / 2.0f) > colB.modifyPosition.y - (colB.height / 2.0f)) &&
//					 (colB.modifyPosition.y + (colB.height / 2.0f) > colA.modifyPosition.y - (colA.height / 2.0f));
//	
//	if (isCollide) {
//		if ((colA.allowOverlap || colB.allowOverlap) == false) {
//			CollisionPush(colA, colB);
//		}
//	}
//
//	return isCollide;
//}
//
//void Collision::CollisionPush(BoxCollider2D& colA, BoxCollider2D& colB) {
//	
//	// acoording to ColA
//
//	bool isAxis_Y = abs(colA.modifyPosition.x - colB.modifyPosition.x) / ((colA.width + colB.width)/2.0f)
//					< abs(colA.modifyPosition.y - colB.modifyPosition.y) / ((colA.height + colB.height) / 2.0f);
//	bool isDir_P;
//	if (isAxis_Y) { isDir_P = (colA.modifyPosition.y > colB.modifyPosition.y); }
//	else{ isDir_P = (colA.modifyPosition.x > colB.modifyPosition.x); }
//	
//
//	if (colA.movable && colB.movable) {		// both
//		//std::cout << "Both Movable" << std::endl;
//		//if (isAxis_Y) {
//		//	colA.transform->position.y = colB.transform->position.y + ((colA.height / 2.0f) /* half way */) * ((isDir_P) ? 1 : -1);
//		//	colB.transform->position.y = colA.transform->position.y + (colB.height * (!isDir_P) /* invert direction */ ? 1 : -1);
//		//}
//		//else {
//		//	colA.transform->position.x = colB.transform->position.x + ((colA.width / 2.0f) /* half way */) * ((isDir_P) ? 1 : -1);
//		//	colB.transform->position.x = colA.transform->position.x + (colB.width * (!isDir_P) /* invert direction */ ? 1 : -1);
//		//}
//	}
//	else if(colA.movable){					// Move A
//		/*std::cout << "A(Player) Movable" << std::endl;*/
//		if (isAxis_Y) {
//			/*std::cout << "Axis Y" << std::endl;
//			std::cout << "PlayerPos_Before: " << colA.transform->position << std::endl;
//			std::cout << "Thresh_X: " << abs(colA.transform->position.x - colB.transform->position.x)
//				<< " Thresh_Y: " << abs(colA.transform->position.y - colB.transform->position.y) << std::endl;
//			std::cout << "NewPos: " << colB.transform->position.y << " + " << (colA.height + colB.height) / 2.0f << std::endl;*/
//			colA.modifyPosition.y = colB.modifyPosition.y + (((colA.height+ colB.height) / 2.0f)  * ((isDir_P) ? 1 : -1));
//			colA.transform->position.y = colA.modifyPosition.y - colA.offsetY;
//			/*std::cout << "PlayerPos_After/: " << colA.transform->position << std::endl << std::endl;*/
//		}
//		else {
//			/*std::cout << "Axis X" << std::endl;
//			std::cout << "PlayerPos_Before: " << colA.transform->position << std::endl;
//			std::cout << "Thresh_X: " << abs(colA.transform->position.x - colB.transform->position.x)
//				<< " Thresh_Y: " << abs(colA.transform->position.y - colB.transform->position.y) << std::endl;
//			std::cout << "PlayerScale: (" << colA.width << ", " << colA.height << ") CollideObj_Scale: (" << colB.width << ", " << colB.height << ")" << std::endl;
//			std::cout << "Pos_A: " << colA.transform->position << "\tPos_B: " << colB.transform->position << std::endl;*/
//			colA.modifyPosition.x = colB.modifyPosition.x + (((colA.width + colB.width) / 2.0f) * ((isDir_P) ? 1 : -1));
//			colA.transform->position.x = colA.modifyPosition.x - colA.offsetX;
//			/*std::cout << "PlayerPos_After/: " << colA.transform->position << std::endl << std::endl;*/
//		}	
//	}
//	else if(colB.movable){					// Move B
//		/*std::cout << "B(TestObj) Movable " << colB.height << " " << colB.width << std::endl;*/
//		if (isAxis_Y) { 
//			colB.transform->position.y = colA.transform->position.y + (((colA.height + colB.height) / 2.0f) * ((!isDir_P) /* invert direction */ ? 1 : -1));
//			colB.transform->position.y = colB.modifyPosition.y - colB.offsetY;
//		}
//		else {
//			colB.transform->position.x = colA.transform->position.x + (((colA.width + colB.width) / 2.0f) * ((!isDir_P) /* invert direction */ ? 1 : -1));
//			colB.transform->position.x = colB.modifyPosition.x - colB.offsetX;
//		}
//	}
//}
//
//
//bool Collision::IsOnGround(GameObject& objA, GameObject& objB) {
//	if (objA.GetComponent<BoxCollider2D>().modifyPosition.y == objB.GetComponent<BoxCollider2D>().modifyPosition.y
//		+ (objA.GetComponent<BoxCollider2D>().height + objB.GetComponent<BoxCollider2D>().height) / 2.0f) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

#include <math.h>
#include "Collision.h"

bool Collision::AABB(BoxCollider2D& colA, BoxCollider2D& colB) {

	bool isCollide = (colA.modifyPosition.x + (colA.width / 2.0f) >= colB.modifyPosition.x - (colB.width / 2.0f)) &&
					 (colB.modifyPosition.x + (colB.width / 2.0f) >= colA.modifyPosition.x - (colA.width / 2.0f))  &&
					 (colA.modifyPosition.y + (colA.height / 2.0f) >= colB.modifyPosition.y - (colB.height / 2.0f)) &&
					 (colB.modifyPosition.y + (colB.height / 2.0f) >= colA.modifyPosition.y - (colA.height / 2.0f));
	return isCollide;
}

bool Collision::CC_AABB(GameObject& objA, GameObject& objB) {	// A is main Obj
	BoxCollider2D& colA = objA.GetComponent<BoxCollider2D>();
	BoxCollider2D& colB = objB.GetComponent<BoxCollider2D>();
	Transform& transformB = *colB.transform;
	RigidBody& rigA = objA.GetComponent<RigidBody>();
		
	//bool isCollide = (colA.modifyPosition.x + (colA.width / 2.0f) + rigA.GetVelocityX() >= colB.modifyPosition.x - (colB.width / 2.0f)) &&		// right_A >= left_B
	//				 (colA.modifyPosition.x - (colA.width / 2.0f) + rigA.GetVelocityX() <= colB.modifyPosition.x + (colB.width / 2.0f)) &&		// left_A <= right_B
	//				 (colA.modifyPosition.y + (colA.height / 2.0f) + rigA.GetVelocityY() >= colB.modifyPosition.y - (colB.height / 2.0f)) &&	// top_A >= bottom_B
	//				 (colA.modifyPosition.y - (colA.height / 2.0f) + rigA.GetVelocityY() <= colB.modifyPosition.y + (colB.height / 2.0f));		// bottom_A <= top_B

	bool right = (colA.modifyPosition.x + (colA.width / 2.0f) + rigA.GetVelocityX() >= colB.modifyPosition.x - (colB.width / 2.0f));		// right_A >= left_B
	bool left = (colA.modifyPosition.x - (colA.width / 2.0f) + rigA.GetVelocityX() <= colB.modifyPosition.x + (colB.width / 2.0f));		// left_A <= right_B
	bool top = (colA.modifyPosition.y + (colA.height / 2.0f) + rigA.GetVelocityY() >= colB.modifyPosition.y - (colB.height / 2.0f));	// top_A >= bottom_B
	
	float bottomA = roundf((colA.modifyPosition.y - (colA.height / 2.0f) + rigA.GetVelocityY()) * 100.0f) / 100.0f;
	float bottomB = roundf((colB.modifyPosition.y + (colB.height / 2.0f)) * 100.0f) / 100.0f;
	bool bottom = bottomA <= bottomB;
		
	bool isCollide = (right && left && top && bottom);

	// calulate next translation
	if (isCollide) {
		if (((colA.allowOverlap || colB.allowOverlap) == false) && (colA.movable != colB.movable)) {
			CC_Collision_Push(rigA, colA, colB, transformB);
		}
		if (colA.iscarried) {
			if (colB.GetTag() == BoxCollider2D::TILE_COLLISION) { colA.isHardCollide = true; }
		}
		//IsOnGround(objA, objB);
	}

	return isCollide;
}

//void Collision::CC_Collision_Push(RigidBody& rigA, BoxCollider2D& colA, BoxCollider2D& colB) {
//
//	bool isAxis_Y = abs(colA.modifyPosition.x + rigA.GetVelocityX() - colB.modifyPosition.x) / ((colA.width + colB.width) / 2.0f)
//					< abs(colA.modifyPosition.y + rigA.GetVelocityY() - colB.modifyPosition.y) / ((colA.height + colB.height) / 2.0f);
//	bool isDir_P;
//	if (isAxis_Y) { isDir_P = (colA.modifyPosition.y + rigA.GetVelocityY() > colB.modifyPosition.y); }
//	else{ isDir_P = (colA.modifyPosition.x +rigA.GetVelocityX() > colB.modifyPosition.x); }
//
//
//	/*std::cout << "\nPreCal----------------------------" << std::endl;
//	std::cout << "Current_Vel:" << rigA.GetVelocity() << std::endl;
//	std::cout << "colA_modifyPosition_X:" << colA.modifyPosition.x << std::endl;
//	std::cout << "colA_modifyPosition_Y:" << colA.modifyPosition.y << std::endl;
//	std::cout << "colB_modifyPosition_X:" << colB.modifyPosition.x << std::endl;
//	std::cout << "colB_modifyPosition_Y:" << colB.modifyPosition.y << std::endl;
//
//	std::cout << "\Vector_PosX:" << abs(colA.modifyPosition.x + rigA.GetVelocityX() - colB.modifyPosition.x) << std::endl;
//	std::cout << "X_Multiplier:" << ((colA.width + colB.width) / 2.0f) << std::endl;
//	std::cout << "Vector_PosY:" << abs(colA.modifyPosition.y + rigA.GetVelocityY() - colB.modifyPosition.y) << std::endl;
//	std::cout << "Y_Multiplier:" << ((colA.height + colB.height) / 2.0f) << std::endl;
//
//	std::cout << "\nRatio_VecX:" << abs(colA.modifyPosition.x + rigA.GetVelocityX() - colB.modifyPosition.x) / ((colA.width + colB.width) / 2.0f) << std::endl;
//	std::cout << "Ratio_VecY:" << abs(colA.modifyPosition.y + rigA.GetVelocityY() - colB.modifyPosition.y) / ((colA.height + colB.height) / 2.0f) << std::endl;
//	std::cout << "isAxisY:" << isAxis_Y << std::endl;
//	std::cout << "isDir_P:" << isDir_P << std::endl; */
//
//	if (isAxis_Y) {
//		//  distance to move = Egde of desired pos - current pos ( currently overlap )
//		float vecPush_Y = colB.modifyPosition.y + (((colA.height + colB.height) / 2.0f) * ((isDir_P) ? 1 : -1)) - (colA.modifyPosition.y + rigA.GetVelocityY()); // not sure
//		rigA.SetVelocityY(rigA.GetVelocityY() + vecPush_Y);
//		/*std::cout << "\nCalY" << std::endl;
//		std::cout << "Edge_Y:" << colB.modifyPosition.y + (((colA.height + colB.height) / 2.0f) * ((isDir_P) ? 1 : -1)) << std::endl;
//		std::cout << "vecPush_Y:" << vecPush_Y << std::endl;
//		std::cout << "vecNew_Y:" << rigA.GetVelocityY() << std::endl;*/
//	}
//	else {
//		//  distance to move = Egde of desired pos - current pos ( currently overlap )
//		float vecPush_X = colB.modifyPosition.x + (((colA.width + colB.width) / 2.0f) * ((isDir_P) ? 1 : -1)) - (colA.modifyPosition.x + rigA.GetVelocityX()); // not sure
//		rigA.SetVelocityX(rigA.GetVelocityX() + vecPush_X);
//		/*std::cout << "\nCalX" << std::endl;
//		std::cout << "Edge_X:" << colB.modifyPosition.x + (((colA.width + colB.width) / 2.0f) * ((isDir_P) ? 1 : -1)) << std::endl;
//		std::cout << "vecPush_X:" << vecPush_X << std::endl;
//		std::cout << "vecNew_X:" << rigA.GetVelocityX() << std::endl;*/
//	}
//	
//	// Check isGround
//	if (isAxis_Y && isDir_P) { colA.SetIsGround(true); }
//
//}

void Collision::CC_Collision_Push(RigidBody& rigA, BoxCollider2D& colA, BoxCollider2D& colB, Transform& transformB) {

	// hotspot var
	std::vector<int> collideSpot;
	int hPerSide = 5;				// for each side (more than 1)
	float percent_Offset = 15;			// where the first point willl be scaling from corner (less than 100)
	
	float firstOffset_X = colA.width * percent_Offset / 100.0f;
	float firstOffset_Y = colA.height * percent_Offset / 100.0f;
	float betweenPoint_X = (colA.width * (100.0f - (percent_Offset * 2)) / 100.0f) / (float)(hPerSide - 1);
	float betweenPoint_Y = (colA.height * (100.0f - (percent_Offset * 2)) / 100.0f) / (float)(hPerSide - 1);
	
	bool checkX = !((colB.GetTag() == BoxCollider2D::DOOR_COLLISION) && (transformB.rotationAngle < 45.0f));
	bool checkY = !((colB.GetTag() == BoxCollider2D::DOOR_COLLISION) && (transformB.rotationAngle > 45.0f));
	bool elevator = (colB.GetTag() == BoxCollider2D::ELEVATOR_COLLISION);
	/*if (colB.GetTag() == BoxCollider2D::DOOR_COLLISION) {
		SR_SYSTEM_TRACE("checkX: {0}", checkX);
		SR_SYSTEM_TRACE("checkY: {0}", checkY);
	}*/

	/*if (checkX) {*/
		// Y_right
		for (int i = 0; i < hPerSide; i++) {
			Vector2D_float hPoint = colA.modifyPosition + rigA.GetVelocity() + Vector2D_float(colA.width / 2.0f, colA.height / 2.0f)/*top-right*/
				+ Vector2D_float(0.0f, -(firstOffset_Y + (float)(betweenPoint_Y * i)));
			bool isCollide = (hPoint.x >= colB.modifyPosition.x - (colB.width / 2.0f)) &&
				(hPoint.x <= colB.modifyPosition.x + (colB.width / 2.0f)) &&
				(hPoint.y >= colB.modifyPosition.y - (colB.height / 2.0f)) &&
				(hPoint.y <= colB.modifyPosition.y + (colB.height / 2.0f));

			if (isCollide) { collideSpot.push_back(1); } // 1 => right
		}


		// Y_left
		for (int i = 0; i < hPerSide; i++) {
			Vector2D_float hPoint = colA.modifyPosition + rigA.GetVelocity() + Vector2D_float(-colA.width / 2.0f, colA.height / 2.0f)/*top-left*/
				+ Vector2D_float(0.0f, -(firstOffset_Y + (float)(betweenPoint_Y * i)));
			bool isCollide = (hPoint.x >= colB.modifyPosition.x - (colB.width / 2.0f)) &&
				(hPoint.x <= colB.modifyPosition.x + (colB.width / 2.0f)) &&
				(hPoint.y >= colB.modifyPosition.y - (colB.height / 2.0f)) &&
				(hPoint.y <= colB.modifyPosition.y + (colB.height / 2.0f));

			if (isCollide) { collideSpot.push_back(2); } // 2 => left
		}
	/*}

	if (checkY) {*/
		// X_Top
		for (int i = 0; i < hPerSide; i++) {
			Vector2D_float hPoint = colA.modifyPosition + rigA.GetVelocity() + Vector2D_float(-colA.width / 2.0f, colA.height / 2.0f)/*top-left*/
				+ Vector2D_float((firstOffset_X + (float)(betweenPoint_X * i)), 0.0f);
			bool isCollide = (hPoint.x >= colB.modifyPosition.x - (colB.width / 2.0f)) &&
				(hPoint.x <= colB.modifyPosition.x + (colB.width / 2.0f)) &&
				(hPoint.y >= colB.modifyPosition.y - (colB.height / 2.0f)) &&
				(hPoint.y <= colB.modifyPosition.y + (colB.height / 2.0f));

			if (isCollide) { collideSpot.push_back(3); } // 3 => top
		}

		// X_Bottom
		for (int i = 0; i < hPerSide; i++) {
			Vector2D_float hPoint = colA.modifyPosition + rigA.GetVelocity() + Vector2D_float(-colA.width / 2.0f, -colA.height / 2.0f)/*bottom-left*/
				+ Vector2D_float((firstOffset_X + (float)(betweenPoint_X * i)), 0.0f);

			hPoint.x = roundf(hPoint.x * 100.0f) / 100.0f;
			hPoint.y = roundf(hPoint.y * 100.0f) / 100.0f;

			bool isCollide = (hPoint.x >= colB.modifyPosition.x - (colB.width / 2.0f)) &&
				(hPoint.x <= colB.modifyPosition.x + (colB.width / 2.0f)) &&
				(hPoint.y >= colB.modifyPosition.y - (colB.height / 2.0f)) &&
				(hPoint.y <= colB.modifyPosition.y + (colB.height / 2.0f));

			if (isCollide) { collideSpot.push_back(4); } // 4 => bottom
		}
	/*}*/
	
	if (collideSpot.empty()) { return; }

	int maxSide		= 0;
	int curSide		= 0;
	int maxCount	= 0;
	int curCount	= 0;
	for (auto i : collideSpot) {
		if (i == curSide) {
			curCount++;
		}
		else if (i != curSide) {
			curSide = i;
			curCount = 1;
		}

		if (curCount > maxCount) {
			maxSide = curSide;
			maxCount = curCount;
		}
	}
	collideSpot.clear();
	
	/*std::cout << maxSide << std::endl;*/

	float vecPush;
	switch (maxSide) {
		case 1: // right
			/*printf("right\n");*/
			if (elevator) { break; }
			vecPush = colB.modifyPosition.x + (((colA.width + colB.width) / 2.0f) * -1 ) - (colA.modifyPosition.x + rigA.GetVelocityX());
			rigA.SetVelocityX(rigA.GetVelocityX() + vecPush);
			break;
		case 2: // left
			/*printf("left\n");*/
			if (elevator) { break; }
			vecPush = colB.modifyPosition.x + (((colA.width + colB.width) / 2.0f) * 1) - (colA.modifyPosition.x + rigA.GetVelocityX());
			rigA.SetVelocityX(rigA.GetVelocityX() + vecPush);
			break;
		case 3:	// top
			/*printf("top\n");*/
			if (elevator) { break; }
			vecPush = colB.modifyPosition.y + (((colA.height + colB.height) / 2.0f) * -1) - (colA.modifyPosition.y + rigA.GetVelocityY());
			rigA.SetVelocityY(rigA.GetVelocityY() + vecPush);
			break;
		case 4: // bottom
			/*printf("bottom\n");*/
			vecPush = roundf((colB.modifyPosition.y + (((colA.height + colB.height) / 2.0f) * 1) - (colA.modifyPosition.y + rigA.GetVelocityY())) * 100.0f) / 100.0f;
			rigA.SetVelocityY(rigA.GetVelocityY() + vecPush);
			colA.SetIsGround(true);
			break;
	}
	
	
}

//bool Collision::IsOnGround(GameObject& objA, GameObject& objB) {
//	if (objA.GetComponent<BoxCollider2D>().modifyPosition.y == objB.GetComponent<BoxCollider2D>().modifyPosition.y
//		+ (objA.GetComponent<BoxCollider2D>().height + objB.GetComponent<BoxCollider2D>().height) / 2.0f) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}