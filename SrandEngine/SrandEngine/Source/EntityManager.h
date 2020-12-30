#pragma once
#include "ECS/GameObject.h"

#include <vector>
#include <memory>

class GameObject;

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	void Draw();
	void Update();
	void Refresh();
	
	void AddEntity(GameObject* _gameObj);
	void DestroyEntity(GameObject* _gameObj);

	GameObject* CloneEntity(GameObject* _gameObj);

private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;
};
