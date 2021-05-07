#pragma once

#include "GUI.h"

namespace Srand
{
	class GUI_Selector : public GUI
	{
	public:
		GUI_Selector();
		GUI_Selector(std::string name);
		virtual ~GUI_Selector();

		virtual bool Init() override final;

		void AttachOrigin(Transform* transform);
		void SetDestination(Transform* transform);
		void IsActive(bool con);

		void Move();
		
		void SetOffset(float x, float y);

	private:
		std::string name = "";

		bool activate = false;
		bool reset = false;

		float xOffset, yOffset;
		bool offsetEnable = false;
		
		/*int steps = 60;
		int stepsCount = 0;
		bool stepsEnd = false;*/

		Transform* origin = nullptr;
		Transform* destination = nullptr;
	};
}
