#pragma once

#include <srpch.h>
#include "ecspch.h"

#include "Source/ObjectManager.h"

namespace Srand 
{
	class Scene 
	{
	protected:
		std::string m_DebugName;

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