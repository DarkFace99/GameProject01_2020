#include "GUI_Array.h"

Srand::GUI_Array::GUI_Array()
{
	m_vector.clear();
	m_index = 0;
	m_vectorIndex = 0;
	name = "";
	m_activate = true;
}
Srand::GUI_Array::GUI_Array(std::string name)
{
	m_vector.clear();
	m_index = 0;
	m_vectorIndex = 0;
	this->name = name;
	m_activate = true;
}
Srand::GUI_Array::~GUI_Array()
{
	Clear();
}

void Srand::GUI_Array::OnDraw()
{
	if (m_activate)
	{
		for (GameObject* obj : m_vector)
			obj->Draw();
	}
}
void Srand::GUI_Array::OnUpdate()
{
	if (m_activate)
	{
		m_vector[m_index]->GetComponent<GUI_Button>().OnSelect();

		if (input.IsKeyPressed(SR_KEY_UP) && !isUpPressed)
		{
			m_vector[m_index]->GetComponent<GUI_Button>().DeSelect();
			m_index = Abs((m_index - 1) % VectorSize());
			isUpPressed = true;
			SR_TRACE("Index: {0}", m_index);
		}
		else if (input.IsKeyPressed(SR_KEY_DOWN) && !isDownPressed)
		{
			m_vector[m_index]->GetComponent<GUI_Button>().DeSelect();
			m_index = Abs((m_index + 1) % VectorSize());
			isDownPressed = true;
			SR_TRACE("Index: {0}", m_index);
		}
		else if (input.IsKeyReleased(SR_KEY_UP) && isUpPressed)
		{
			//m_index = Abs((m_index - 1) % VectorSize());
			isUpPressed = false;
			//SR_TRACE("Index: {0}", m_index);
		}
		else if (input.IsKeyReleased(SR_KEY_DOWN) && isDownPressed)
		{
			//m_index = Abs((m_index + 1) % VectorSize());
			isDownPressed = false;
			//SR_TRACE("Index: {0}", m_index);
		}
		/*else if (temp->GetComponent<GUI>().GetType() == GUI::Type::SLIDER && input.IsKeyReleased(SR_KEY_RIGHT))
		{

		}
		else if (temp->GetComponent<GUI>().GetType() == GUI::Type::SLIDER && input.IsKeyReleased(SR_KEY_LEFT))
		{

		}*/

		/* Activate key */
		if (input.IsKeyPressed(SR_KEY_SPACE))
		{
			m_vector[m_index]->GetComponent<GUI_Button>().OnActivate();
		}
	}
}
void Srand::GUI_Array::Clear()
{
	m_vector.clear();
	m_index = 0;
	m_vectorIndex = 0;
	name.clear();
	m_activate = true;
}

void Srand::GUI_Array::PushGUI(GameObject* gui)
{
	m_vector.emplace(m_vector.begin() + m_vectorIndex, gui);
	m_vector[m_vectorIndex]->GetComponent<GUI_Button>().SetIndex(m_vectorIndex);
	m_vectorIndex++;
}
