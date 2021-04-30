#pragma once

#include "GUI.h"
#include "ECS/TileSelector.h"

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
		virtual void DeSelect() override;
		virtual void OnActivate() override;

		void SetIndex(int i);
		int GetIndex();
		
		void SelectedOffset(int, int);
	private:
		std::string name = "";
		int currentIndex = 0;

		TileSelector* tileSelector = nullptr;
		int originX, originY, shiftX, shiftY;
		bool isSelected = false;
		bool isShifted = false;
	};
}
