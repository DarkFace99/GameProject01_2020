#include "Collision.h"

bool Collision::AABB(BoxCollider2D& colA, BoxCollider2D& colB) {
	bool isCollide = (colA.transform->position.x + colA.width >= colB.transform->position.x) &&	
					 (colB.transform->position.x + colB.width >= colA.transform->position.x) &&
					 (colA.transform->position.y + colA.height >= colB.transform->position.y) &&
					 (colB.transform->position.y + colB.height >= colA.transform->position.y);
	
	if (isCollide) {
		if ((colA.allowOverlap || colB.allowOverlap) == false) {
			CollisionPush(colA, colB);
		}
	}

	return isCollide;
}

void Collision::CollisionPush(BoxCollider2D& colA, BoxCollider2D& colB) {
	
	// acoording to ColA
	bool isAxis_Y = (abs(colA.transform->position.x - colB.transform->position.x) < abs(colA.transform->position.y - colB.transform->position.y));
	bool isDir_P;
	if (isAxis_Y) { isDir_P = (colA.transform->position.y > colB.transform->position.y); }
	else{ isDir_P = (colA.transform->position.x > colB.transform->position.x); }
	

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
		std::cout << "A(Player) Movable" << std::endl;
		if (isAxis_Y) {
			colA.transform->position.y = colB.transform->position.y + (colA.height * ((isDir_P) ? 1 : -1));
		}
		else {
			colA.transform->position.x = colB.transform->position.x + (colA.width * ((isDir_P) ? 1 : -1));
		}	
	}
	else if(colB.movable){					// Move B
		std::cout << "B(TestObj) Movable " << colB.height << " " << colB.width << std::endl;
		if (isAxis_Y) { 
			
			colB.transform->position.y = colA.transform->position.y + (colB.height * ((!isDir_P) /* invert direction */ ? 1 : -1));
		}
		else {
			colB.transform->position.x = colA.transform->position.x + (colB.width * ((!isDir_P) /* invert direction */ ? 1 : -1));
		}
	}
}