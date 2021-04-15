#pragma once

#include <srpch.h>

#include "WindowsInput.h"
#include "KeyCode.h"
#include "GUI_Button.h"

namespace Srand
{
	class GUI_Array
	{
	public:
		GUI_Array();
		GUI_Array(std::string name);
		~GUI_Array();

		void OnUpdate();
		void Clear();

		inline void SetName(std::string name) { this->name = name; }
		inline void SetStatus(bool status) { this->m_activate = status; }

		inline unsigned int Index() { return m_index; }
		inline bool GetStatus() { return m_activate; }

		inline int VectorSize() { return m_vector.size(); }
		inline GUI* operator[](int i) { return m_vector[i]; }

		inline std::vector<GUI*>::iterator begin() { return m_vector.begin(); }
		inline std::vector<GUI*>::iterator end() { return m_vector.end(); }

	private:
		std::vector<GUI*> m_vector;
		std::string name;
		unsigned int m_index;

		bool m_activate;

		WindowsInput input;
	};
}