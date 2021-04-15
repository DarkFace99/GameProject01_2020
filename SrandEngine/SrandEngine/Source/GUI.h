#pragma once

#include <srpch.h>
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

	private:
		Vector2D_float center;
		Vector2D_float dimension;
	};
}
