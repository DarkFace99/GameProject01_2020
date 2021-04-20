#pragma once

#include <srpch.h>
#include <ecspch.h>
#include "ECS/Component.h"

#include "WindowsInput.h"
#include "Vector2D.h"

namespace Srand
{
	typedef void (*_FUNC)();

	class GUI : public Component
	{
	public:
		enum state 
		{
			SELECT,
			ACTIVATE
		};

		GUI();
		GUI(Vector2D_float center, Vector2D_float dimension);

		virtual void Initialize();

		void Connect(_FUNC func);

		virtual void OnSelect();
		virtual void OnActivate();

	protected:
		Vector2D_float center;
		Vector2D_float dimension;

		_FUNC m_function = nullptr;

		WindowsInput input;

		Transform* transform = nullptr;
		SpriteRenderer* renderer = nullptr;
	};
}
