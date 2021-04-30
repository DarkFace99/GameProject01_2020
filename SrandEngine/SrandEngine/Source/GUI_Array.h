#pragma once

#include <srpch.h>

#include "WindowsInput.h"
#include "KeyCode.h"
#include "GUI_Button.h"
#include "GUI_Slider.h"
#include "GUI_Text.h"

namespace Srand
{
	class GUI_Array
	{
	public:
		GUI_Array();
		GUI_Array(std::string name);
		~GUI_Array();

		void OnDraw();
		void OnUpdate();
		void Clear();

		inline void SetName(std::string name) { this->name = name; }
		inline void SetStatus(bool status) { this->m_activate = status; }

		void PushGUI(GameObject* gui);

		inline unsigned int Index() { return m_index; }
		inline bool GetStatus() { return m_activate; }

		inline int VectorSize() { return m_vector.size(); }
		inline GameObject* operator[](int i) { return m_vector[i]; }

		inline std::vector<GameObject*>::iterator begin() { return m_vector.begin(); }
		inline std::vector<GameObject*>::iterator end() { return m_vector.end(); }

		std::vector<GameObject*> m_interactable;
	private:
		std::vector<GameObject*> m_vector;	
		std::string name;
		unsigned int m_index;
		int m_vectorIndex;

		bool m_activate;
		bool isUpPressed = false;
		bool isDownPressed = false;

		WindowsInput input;
	};
}