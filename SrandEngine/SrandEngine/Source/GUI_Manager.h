#pragma once

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
		virtual ~GUI_Manager();

	private:
		static GUI_Manager* s_instance;
		GUI_Manager();

	};
}
