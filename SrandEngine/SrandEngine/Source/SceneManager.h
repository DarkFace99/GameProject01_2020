#pragma once

#include <srpch.h>
#include "ecspch.h"

#include "EntityManager.h"
#include "Source/Scene.h"

namespace Srand 
{
	class Scene;

	class SceneManager 
	{
	private:
		static SceneManager* s_instance;
		EntityManager* manager = nullptr;

		std::vector<Scene*> m_sceneVector;
		int m_currentLevelIndex = 0;
		int m_maxLevelIndex = 0;
		unsigned int m_vectorIndex = 0;

		SceneManager();

	public:
		virtual ~SceneManager();
		static SceneManager& get() 
		{
			if (!s_instance) 
			{
				s_instance = new SceneManager();
			}
			return *s_instance;
		}

		void PushScene(Scene* sce);
		void PopScene(Scene* sce);
		Scene* Search(Scene* sce);
		Scene* Search(const std::string name);

		void Clear();

		inline int VectorSize() { return m_sceneVector.size(); }
		Scene* operator[](int i) { return m_sceneVector[i]; }

		std::vector<Scene*>::iterator begin() { return m_sceneVector.begin(); }
		std::vector<Scene*>::iterator end() { return m_sceneVector.end(); }

		inline void SetMaxIndex(int i) 
		{ 
			if(m_maxLevelIndex <= i)
			m_maxLevelIndex = i; 
		}
		inline int GetMaxIndex() { return m_maxLevelIndex; }
	};
}
