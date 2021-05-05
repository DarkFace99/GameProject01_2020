#pragma once

#include "GUI.h"

namespace Srand
{
	class GUI_Text : public GUI
	{
	public:
		GUI_Text();
		GUI_Text(std::string name);
		virtual ~GUI_Text();

		virtual bool Init() override final;

	private:
		std::string name = "";

	};
}