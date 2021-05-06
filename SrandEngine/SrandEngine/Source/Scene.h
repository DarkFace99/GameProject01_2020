#pragma once

#include <srpch.h>
#include "ecspch.h"

#include "Source/ObjectManager.h"
#include "Source/LevelManager.h"
#include "Source/GUI_Manager.h"

#include "Source/Camera.h"

#include "Entity/Button.h"
#include "Entity/Door.h"
#include "Entity/Elevator.h"
#include "Entity/NPC.h"
#include "Entity/Benny.h"
#include "Entity/Macho.h"
#include "Entity/Cherry.h"
#include "Entity/Pear.h"
#include "Entity/Barter.h"

#include "Source/Audio.h"


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

		Camera camera = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);
		ObjManager& objManager = ObjManager::get();
		LevelManager& levelManager = LevelManager::get();
		AudioController& audioController = AudioController::get();
		//GUI_Manager& guiManager = GUI_Manager::get();

		GameObject* gameObject = nullptr;
		GameObject* button1 = nullptr;
		GameObject* button2 = nullptr;
		GameObject* button3 = nullptr;

		int progress = 3;

	public:
		Scene(const std::string& name = "Scene")
			: m_DebugName(name) 
		{}
		virtual ~Scene() {}

		virtual void Init() {}
		virtual void Clean() {}
		virtual void Draw() {}
		virtual void Update() {}

		inline const std::string& GetName() const { return m_DebugName; }

		inline void SetProgress(int proc) { progress = proc; }
		inline int GetProgress() { return progress; }
	};
}