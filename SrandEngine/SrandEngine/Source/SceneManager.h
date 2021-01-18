#pragma once

#include <srpch.h>
#include "ecspch.h"

#include "EntityManager.h"

namespace Srand 
{
	class SceneManager 
	{
	private:
		static SceneManager* s_instance;
		int m_currentLevel;
		EntityManager* manager = nullptr;

		SceneManager();

	public:
		std::vector<GameObject*> objManager;
		GameObject* npc;
		GameObject* player;

		virtual ~SceneManager() = default;
		static SceneManager& get() 
		{
			if (!s_instance) 
			{
				s_instance = new SceneManager();
			}
			return *s_instance;
		}

		void Init();
		void Clean();

		void Draw();
		void Update();

		void SceneCheck();

	};
}
