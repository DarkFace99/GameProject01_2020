#include "GUI_Array.h"

Srand::GUI_Array::GUI_Array()
{
	m_vector.clear();
	m_index = 0;
	name = "";
}
Srand::GUI_Array::GUI_Array(std::string name)
{
	m_vector.clear();
	m_index = 0;
	this->name = name;
}
Srand::GUI_Array::~GUI_Array()
{
	Clear();
}

void Srand::GUI_Array::OnUpdate()
{
	if (input.IsKeyPressed(SR_KEY_UP)) 
	{
		m_index = Abs((m_index - 1) % VectorSize());
	}
	else if (input.IsKeyPressed(SR_KEY_DOWN)) 
	{
		m_index = Abs((m_index + 1) % VectorSize());
	}

	/* Activate key */
	if (input.IsKeyPressed(SR_KEY_SPACE))
	{
		m_vector[m_index]->OnActivate();
	}
}
void Srand::GUI_Array::Clear()
{
	m_vector.clear();
	m_index = 0;
	name.clear();
}
