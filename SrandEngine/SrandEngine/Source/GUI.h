#pragma once

#include <srpch.h>

#include "WindowsInput.h"
#include "Vector2D.h"

namespace Srand
{
	class GUI
	{
	public:
		GUI() {}
		GUI(Vector2D_float center, Vector2D_float dimension)
			: center(center), dimension(dimension)
		{}

		virtual void OnSelect() {}
		virtual void OnActivate() {}

	protected:
		Vector2D_float center;
		Vector2D_float dimension;

		WindowsInput input;
	};
}
