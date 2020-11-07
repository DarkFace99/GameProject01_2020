#pragma once

#include <vector>
#include <memory>

class Entity;

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	void Draw();
	void Update();
	void Refresh();

	void AddEntity(Entity* _gameObj);
	void DestroyEntity(Entity* _gameObj);

	Entity* CloneEntity(Entity* _gameObj);

private:

};

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}
