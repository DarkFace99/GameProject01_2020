#include "Collision.h"

bool Collision::AABB(BoxCollider2D& colA, BoxCollider2D& colB) {
	bool isCollide = (colA.modifyPosition.x + (colA.width / 2.0f) >= colB.modifyPosition.x - (colB.width / 2.0f)) &&
					 (colB.modifyPosition.x + (colB.width / 2.0f) >= colA.modifyPosition.x - (colA.width / 2.0f)) &&
					 (colA.modifyPosition.y + (colA.height / 2.0f) >= colB.modifyPosition.y - (colB.height / 2.0f)) &&
					 (colB.modifyPosition.y + (colB.height / 2.0f) >= colA.modifyPosition.y - (colA.height / 2.0f));
	
	if (isCollide) {
		if ((colA.allowOverlap || colB.allowOverlap) == false) {
			CollisionPush(colA, colB);
		}
	}

	return isCollide;
}

void Collision::CollisionPush(BoxCollider2D& colA, BoxCollider2D& colB) {
	
	// acoording to ColA

	bool isAxis_Y = abs(colA.modifyPosition.x - colB.modifyPosition.x) / ((colA.width + colB.width)/2.0f)
					< abs(colA.modifyPosition.y - colB.modifyPosition.y) / ((colA.height + colB.height) / 2.0f);
	bool isDir_P;
	if (isAxis_Y) { isDir_P = (colA.modifyPosition.y > colB.modifyPosition.y); }
	else{ isDir_P = (colA.modifyPosition.x > colB.modifyPosition.x); }
	

	if (colA.movable && colB.movable) {		// both
		//std::cout << "Both Movable" << std::endl;
		//if (isAxis_Y) {
		//	colA.transform->position.y = colB.transform->position.y + ((colA.height / 2.0f) /* half way */) * ((isDir_P) ? 1 : -1);
		//	colB.transform->position.y = colA.transform->position.y + (colB.height * (!isDir_P) /* invert direction */ ? 1 : -1);
		//}
		//else {
		//	colA.transform->position.x = colB.transform->position.x + ((colA.width / 2.0f) /* half way */) * ((isDir_P) ? 1 : -1);
		//	colB.transform->position.x = colA.transform->position.x + (colB.width * (!isDir_P) /* invert direction */ ? 1 : -1);
		//}
	}
	else if(colA.movable){					// Move A
		/*std::cout << "A(Player) Movable" << std::endl;*/
		if (isAxis_Y) {
			/*std::cout << "Axis Y" << std::endl;
			std::cout << "PlayerPos_Before: " << colA.transform->position << std::endl;
			std::cout << "Thresh_X: " << abs(colA.transform->position.x - colB.transform->position.x)
				<< " Thresh_Y: " << abs(colA.transform->position.y - colB.transform->position.y) << std::endl;
			std::cout << "NewPos: " << colB.transform->position.y << " + " << (colA.height + colB.height) / 2.0f << std::endl;*/
			colA.modifyPosition.y = colB.modifyPosition.y + (((colA.height+ colB.height) / 2.0f)  * ((isDir_P) ? 1 : -1));
			colA.transform->position.y = colA.modifyPosition.y - colA.offsetY;
			/*std::cout << "PlayerPos_After/: " << colA.transform->position << std::endl << std::endl;*/
		}
		else {
			/*std::cout << "Axis X" << std::endl;
			std::cout << "PlayerPos_Before: " << colA.transform->position << std::endl;
			std::cout << "Thresh_X: " << abs(colA.transform->position.x - colB.transform->position.x)
				<< " Thresh_Y: " << abs(colA.transform->position.y - colB.transform->position.y) << std::endl;
			std::cout << "PlayerScale: (" << colA.width << ", " << colA.height << ") CollideObj_Scale: (" << colB.width << ", " << colB.height << ")" << std::endl;
			std::cout << "Pos_A: " << colA.transform->position << "\tPos_B: " << colB.transform->position << std::endl;*/
			colA.modifyPosition.x = colB.modifyPosition.x + (((colA.width + colB.width) / 2.0f) * ((isDir_P) ? 1 : -1));
			colA.transform->position.x = colA.modifyPosition.x - colA.offsetX;
			/*std::cout << "PlayerPos_After/: " << colA.transform->position << std::endl << std::endl;*/
		}	
	}
	else if(colB.movable){					// Move B
		/*std::cout << "B(TestObj) Movable " << colB.height << " " << colB.width << std::endl;*/
		if (isAxis_Y) { 
			colB.transform->position.y = colA.transform->position.y + (((colA.height + colB.height) / 2.0f) * ((!isDir_P) /* invert direction */ ? 1 : -1));
			colB.transform->position.y = colB.modifyPosition.y - colB.offsetY;
		}
		else {
			colB.transform->position.x = colA.transform->position.x + (((colA.width + colB.width) / 2.0f) * ((!isDir_P) /* invert direction */ ? 1 : -1));
			colB.transform->position.x = colB.modifyPosition.x - colB.offsetX;
		}
	}
}


bool Collision::IsOnGround(GameObject& objA, GameObject& objB) {
	if (objA.GetComponent<BoxCollider2D>().modifyPosition.y == objB.GetComponent<BoxCollider2D>().modifyPosition.y
		+ (objA.GetComponent<BoxCollider2D>().height + objB.GetComponent<BoxCollider2D>().height) / 2.0f) {
		return true;
	}
	else {
		return false;
	}
}