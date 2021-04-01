#pragma once

#include <srpch.h>
#include "Vector2D.h"
#include "WindowsInput.h"

namespace Srand
{
	class GUI
	{
	public:
		GUI();
		GUI(Vector2D_float center, Vector2D_float dimension);

		void OnClick();
		void OnHold();

	private:
		Vector2D_float center;
		Vector2D_float dimension;

		WindowsInput input;
	};
}
