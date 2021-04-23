#pragma once

#include "GUI.h"

namespace Srand 
{
	class GUI_Button : public GUI
	{
	public:
		GUI_Button();
		GUI_Button(std::string name);
		virtual ~GUI_Button();

		virtual bool Init() override final;
		virtual void Update() override final;

		virtual void OnSelect() override;
		virtual void OnActivate() override;

		void SetIndex(int i);
		int GetIndex();
		
	private:
		std::string name = "";
		int currentIndex = 0;

	};
}
