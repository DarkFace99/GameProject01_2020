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
		void IsChoosing(bool con);

		void Move();

	private:
		std::string name = "";

		bool activate = false;
		Transform* origin = nullptr;
		Transform* destination = nullptr;
	};
}
