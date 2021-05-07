#pragma once

#include "GUI.h"
#include "ECS/Animator.h"

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
		void SetPercentRange(float percent);

	private:
		std::string name = "";

		bool activate = false;
		bool reset = false;

		float xOffset, yOffset;
		bool offsetEnable = false;

		float percentRange = 0;
		
		/*int steps = 60;
		int stepsCount = 0;
		bool stepsEnd = false;*/

		Transform* origin = nullptr;
		Transform* destination = nullptr;
		Animator* animator = nullptr;
	};
}
