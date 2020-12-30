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
	void Clean();
	
	void AddEntity(GameObject* _gameObj);
	void DestroyEntity(GameObject* _gameObj);

	GameObject* CloneEntity(GameObject* _gameObj);

	static EntityManager& get()
	{
		if (!s_instance)
		{
			s_instance = new EntityManager();
		}
		return *s_instance;
	}

private:
	static EntityManager* s_instance;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
};
