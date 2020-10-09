#pragma once
#include <iostream>
#include <cmath>
#include "Renderable.h"
#include "GameObject.h"

class Collision : public GameObject
{
private:
	GameObject gameObject_Arr[MAX_INSTANCE_GAMEOBJECTS];

	bool isCollide = false;
	GameObject objectCollided_with;

	void Set_isCollde(bool col);
	void Set_CollideWith(GameObject col_With);

public:
	Collision CollisionRvR(GameObject* gameObject_Arr);

	bool Get_isCollide();
	int Get_collideWith();

};
