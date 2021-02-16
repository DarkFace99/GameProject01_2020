#include "EntityManager.h"
#include "ECS/SpriteRenderer.h"

namespace Srand 
{
	EntityManager* EntityManager::s_instance = nullptr;

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
		for (auto& gameObject : gameObjects)
		{
			gameObject->Update();
		}
	}
	void EntityManager::Clean()
	{
		// Clean when changing scene
		gameObjects.clear();
	}

	void EntityManager::AddEntity(GameObject* _gameObj)
	{
		std::unique_ptr<GameObject> uniquePtr{ _gameObj };
		gameObjects.emplace_back(std::move(uniquePtr));

		//std::cout << "Entity Added " << _gameObj->HasComponent<Transform>() << std::endl; // Just to check
	}
	void EntityManager::DestroyEntity(GameObject* _gameObj)
	{
		std::unique_ptr<GameObject> uniquePtr{ _gameObj };
		auto it = std::find(gameObjects.begin(), gameObjects.end(), uniquePtr);
		if (it != gameObjects.end())
		{
			gameObjects.erase(it);
		}
	}

	GameObject* EntityManager::CloneEntity(GameObject* _gameObj)
	{
		return nullptr;
	}
}
