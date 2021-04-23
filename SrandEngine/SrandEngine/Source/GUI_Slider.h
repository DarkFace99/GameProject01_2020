#pragma once

#include "GUI.h"

namespace Srand
{
	class GUI_Slider : GUI
	{
	public:
		GUI_Slider();
		GUI_Slider(std::string name);
		virtual ~GUI_Slider();

		virtual void OnSelect() override;
		virtual void OnActivate() override;

	private:
		std::string name = "";

	};
}