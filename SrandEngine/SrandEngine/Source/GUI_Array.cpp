#include "GUI_Array.h"

Srand::GUI_Array::GUI_Array()
{
	m_vector.clear();
	m_index = 0;
	name = "";
	m_activate = true;
}
Srand::GUI_Array::GUI_Array(std::string name)
{
	m_vector.clear();
	m_index = 0;
	this->name = name;
	m_activate = true;
}
Srand::GUI_Array::~GUI_Array()
{
	Clear();
}

void Srand::GUI_Array::OnUpdate()
{
	GUI* temp = m_vector[m_index];

	m_vector[m_index]->OnSelect();

	if (input.IsKeyReleased(SR_KEY_UP)) 
	{
		m_index = Abs((m_index - 1) % VectorSize());
	}
	else if (input.IsKeyReleased(SR_KEY_DOWN))
	{
		m_index = Abs((m_index + 1) % VectorSize());
	}
	else if (temp->GetType() == GUI::Type::SLIDER && input.IsKeyReleased(SR_KEY_RIGHT))
	{
		
	}
	else if (temp->GetType() == GUI::Type::SLIDER && input.IsKeyReleased(SR_KEY_LEFT))
	{
		
	}

	/* Activate key */
	if (input.IsKeyReleased(SR_KEY_SPACE))
	{
		m_vector[m_index]->OnActivate();
	}
}
void Srand::GUI_Array::Clear()
{
	m_vector.clear();
	m_index = 0;
	name.clear();
	m_activate = true;
}
