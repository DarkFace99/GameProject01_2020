#include "Collision.h"

Collision Collision::CollisionRvR(GameObject* gameObject_Arr)
{
	Collision collidingCheck;
	for (int i = 0; i < MAX_INSTANCE_GAMEOBJECTS; i++) 
	{
		GameObject* pointerObj_1 = gameObject_Arr + i;

		if (pointerObj_1->GetFlag() == FLAG_INACTIVE_GAMEOBJECT) continue;

		if (pointerObj_1->GetControl() == IN_CONTROLLED) 
		{
			// Comparing the Controlled Character with other Object in the Game
			for (int j = 0; j < MAX_INSTANCE_GAMEOBJECTS; j++) 
			{
				GameObject* pointerObj_2 = gameObject_Arr + i;
				// Skip incactive GameObject
				if (pointerObj_2->GetFlag() == FLAG_INACTIVE_GAMEOBJECT) continue;

				if (pointerObj_2->GetTag() == OBSTACLES) 
				{
					// Check for collsion
					bool collide = true;

					if ((pointerObj_1->GetPosition().x - pointerObj_1->GetScale().x / 3.0f) > (pointerObj_2->GetPosition().x + pointerObj_2->GetScale().x / 3.0f)) { collide = false; }
					if ((pointerObj_2->GetPosition().x - pointerObj_2->GetScale().x / 3.0f) > (pointerObj_1->GetPosition().x + pointerObj_1->GetScale().x / 3.0f)) { collide = false; }
					if ((pointerObj_1->GetPosition().y - pointerObj_1->GetScale().y / 3.0f) > (pointerObj_2->GetPosition().y + pointerObj_2->GetScale().y / 3.0f)) { collide = false; }
					if ((pointerObj_2->GetPosition().y - pointerObj_2->GetScale().y / 3.0f) > (pointerObj_1->GetPosition().y + pointerObj_1->GetScale().y / 3.0f)) { collide = false; }

					if (collide) {
						// Update game behavior and sGameObjInstArray
						collidingCheck.Set_CollideWith(*pointerObj_2);
						collidingCheck.Set_isCollde(true);

						return collidingCheck;
					}
				}

			}
		}
	}
}

void Collision::Set_isCollde(bool col) 
{
	isCollide = col;
}
void Collision::Set_CollideWith(GameObject col_With) 
{
	objectCollided_with = col_With;
}

bool Collision::Get_isCollide() 
{
	return isCollide;
}
int Collision::Get_collideWith() 
{
	return objectCollided_with.GetTag();
}