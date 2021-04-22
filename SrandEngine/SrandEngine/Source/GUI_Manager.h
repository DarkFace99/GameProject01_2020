#pragma once

#include <srpch.h>

#include "GUI_Array.h"

namespace Srand 
{
	class GUI_Manager 
	{
	public:
		inline static GUI_Manager& get() 
		{
			if (s_instance == nullptr)
				s_instance = new GUI_Manager();

			return *s_instance;
		}
		virtual ~GUI_Manager() {}

		void AddGUI(GUI_Array* arr);


	private:
		static GUI_Manager* s_instance;
		GUI_Manager();

		std::unordered_map<std::string, GUI_Array*> m_map;

	};
}
