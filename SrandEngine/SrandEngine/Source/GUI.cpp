#include "GUI.h"

namespace Srand
{
	GUI::GUI()
	{
		//Initialize();
	}
	GUI::GUI(Vector2D_float center, Vector2D_float dimension)
		:center(center), dimension(dimension)
	{
		//Initialize();
	}

	void GUI::Initialize() 
	{
		transform = &gameObject->GetComponent<Transform>();
		renderer = &gameObject->GetComponent<SpriteRenderer>();
	}

	/*void GUI::Connect(_FUNC func)
	{
		m_function = func;
	}*/

	void GUI::DeSelect()
	{

	}

	void GUI::OnSelect()
	{

	}
	void GUI::OnActivate()
	{
		m_function();
		SR_TRACE("Button {0}: Activated");
	}

}