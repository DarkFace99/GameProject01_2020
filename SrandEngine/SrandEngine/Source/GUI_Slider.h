#pragma once

#include "GUI.h"

namespace Srand
{
	class GUI_Slider : public GUI
	{
	public:
		GUI_Slider();
		GUI_Slider(std::string name);
		virtual ~GUI_Slider();

		virtual bool Init() override final;
		virtual void Update() override final;

		virtual void OnSelect() override;
		virtual void DeSelect() override;
		virtual void OnActivate() override;

		void AdjustStep();
		void Conceal();

		std::vector<GameObject*> steps;
		int currentStep = 0;

		void ChangeStep(int num);

	private:
		std::string name = "";
		bool isSelected = false;
		bool isConcealed = false;
		bool isRightPressed = false;
		bool isLeftPressed = false;
	};
}