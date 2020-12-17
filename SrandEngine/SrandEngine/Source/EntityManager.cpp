#include "EntityManager.h"
#include "SpriteRenderer.h"
void EntityManager::Draw() 
{
	for (int i = SpriteRenderer::LAYER_START; i < SpriteRenderer::LAYER_END; i++) { // loop through each layer
		for (auto& gameObject : gameObjects)
		{
			if (gameObject->GetComponent<SpriteRenderer>().GetTag() == i) {
				gameObject->Draw();
			}
		}
	}
}

void EntityManager::Update()
{
	for(auto & gameObject : gameObjects)
	{
		gameObject->Update();
	}
}
void EntityManager::Refresh()
{

}

void EntityManager::AddEntity(GameObject* _gameObj)
{
	std::unique_ptr<GameObject> uniquePtr{ _gameObj };
	gameObjects.emplace_back(std::move(uniquePtr));

	//std::cout << "Entity Added " << _gameObj->HasComponent<Transform>() << std::endl; // Just to check
}
void EntityManager::DestroyEntity(GameObject* _gameObj)
{

}

GameObject* EntityManager::CloneEntity(GameObject* _gameObj)
{
	return nullptr;
}