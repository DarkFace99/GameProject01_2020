#include "SceneManager.h"

#include "Source/WindowsInput.h"

#include "Entity/Button.h"
#include "Entity/Door.h"
#include "Entity/Elevator.h"
#include "Entity/NPC.h"

#define RATIO SCREEN_WIDTH / 480.0f

namespace Srand 
{
	SceneManager* SceneManager::s_instance = nullptr;

	SceneManager::SceneManager() 
	{
		
	}
	SceneManager::~SceneManager()
	{
		for (Scene* scene : m_sceneVector)
			delete scene;
		delete s_instance;
	}

	void SceneManager::PushScene(Scene* sce)
	{
		m_sceneVector.emplace(m_sceneVector.begin() + m_vectorIndex, sce);
		m_vectorIndex++;
	}
	void SceneManager::PopScene(Scene* sce)
	{
		auto it = std::find(m_sceneVector.begin(), m_sceneVector.end(), sce);
		if (it != m_sceneVector.end())
		{
			m_sceneVector.erase(it);
			m_vectorIndex--;
		}
	}
	Scene* SceneManager::Search(Scene* sce)
	{
		auto it = std::find(m_sceneVector.begin(), m_sceneVector.end(), sce);
		return *it;
	}
	Scene* SceneManager::Search(const std::string name)
	{
		for (Scene* scene : m_sceneVector)
		{
			if (scene->GetName() == name)
				return scene;
		}
	}
}