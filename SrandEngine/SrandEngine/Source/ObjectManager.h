#pragma once

#include <srpch.h>
#include "ecspch.h"

namespace Srand
{
	class ObjManager
	{
	private:
		std::vector<GameObject*> m_objVector;
		unsigned int m_vectorIndex = 0;

		ObjManager() {}
		static ObjManager* s_instance;

	public:
		static ObjManager& get() 
		{
			if (s_instance == nullptr)
				s_instance = new ObjManager();

			return *s_instance;
		}
		~ObjManager()
		{
			for (GameObject* obj : m_objVector)
				delete obj;
			delete s_instance;
		}
		inline void PushObject(GameObject* obj)
		{
			m_objVector.emplace(m_objVector.begin() + m_vectorIndex, obj);
			m_vectorIndex++;
		}
		inline void PopObject(GameObject* obj)
		{
			auto it = std::find(m_objVector.begin(), m_objVector.end(), obj);
			if (it != m_objVector.end())
			{
				m_objVector.erase(it);
				m_vectorIndex--;
			}
		}
		inline void Clean() 
		{
			m_objVector.clear();
			m_vectorIndex = 0;
		}

		inline int VectorSize() { return m_objVector.size(); }
		GameObject* operator[](int i) { return m_objVector[i]; }

		std::vector<GameObject*>::iterator begin() { return m_objVector.begin(); }
		std::vector<GameObject*>::iterator end() { return m_objVector.end(); }
	};
}
