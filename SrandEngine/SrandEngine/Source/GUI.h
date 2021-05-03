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
		enum class State 
		{
			SELECT,
			ACTIVATE
		};
		enum class Type
		{
			DEFAULT,
			BUTTON,
			SLIDER,
			TEXT
		};

		inline void SetType(Type tag) { m_type = tag; }
		inline Type GetType() const { return m_type; }

		GUI();
		GUI(Vector2D_float center, Vector2D_float dimension);

		virtual void Initialize();

		//void Connect(_FUNC func);

		virtual void OnSelect();
		virtual void DeSelect();
		virtual void OnActivate();

		_FUNC m_function = nullptr; 
		_FUNC n_function = nullptr; 
	protected:
		Vector2D_float center;
		Vector2D_float dimension;

		Transform* transform = nullptr;
		SpriteRenderer* renderer = nullptr;

		Type m_type = Type::DEFAULT;

		WindowsInput input;
	};
}
