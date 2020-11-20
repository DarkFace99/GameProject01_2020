#include <iostream>

#include "ECS.h"
#include "GameObject.h"
#include "Transform.h"
#include "EntityManager.h"


//int main(void) 
//{
//	EntityManager* manager = new EntityManager();
//
//	GameObject* gameObj = new GameObject(); // Create GameObject
//
//	manager->AddEntity(gameObj);// Add gameObject to the Manager
//
//	gameObj->GetComponent<Transform>().position = Vector2D_float(250, 300);
//
//	while (true) // GameLoop 
//	{
//		manager->Draw();
//		manager->Update();
//	}
//
//	std::cout << "gameObj.Transform.Position: " << gameObj->GetComponent<Transform>().position << std::endl;
//	std::cout << "Component ID: " << GetComponentID<Transform>() << std::endl;
//	std::cout << "has Component Transform: " << gameObj->HasComponent<Transform>() << std::endl << std::endl;
//
//
//
//	system("pause");
//	return 0;
//}
