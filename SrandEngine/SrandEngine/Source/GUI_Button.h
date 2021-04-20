#pragma once

#include "GUI.h"

namespace Srand 
{
	class GUI_Button : GUI
	{
	public:
		GUI_Button();
		GUI_Button(std::string name);
		virtual ~GUI_Button();

		virtual void OnSelect() override;
		virtual void OnActivate() override;
		
	private:
		std::string name = "";

	};
}
