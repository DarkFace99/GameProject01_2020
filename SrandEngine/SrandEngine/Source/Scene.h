#pragma once

#include <srpch.h>
#include "ecspch.h"

#include "Source/ObjectManager.h"
#include "Source/LevelManager.h"



namespace Srand 
{
	class Scene 
	{
	protected:
		std::string m_DebugName;

		const int _tileSize = 16;
		const int _offset = 8;
		const int _midPointX = -240;
		const int _midPointY = -135;

	public:
		Scene(const std::string& name = "Scene");
		virtual ~Scene();

		virtual void Init() {}
		virtual void Clean() {}
		virtual void Draw() {}
		virtual void Update() {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}