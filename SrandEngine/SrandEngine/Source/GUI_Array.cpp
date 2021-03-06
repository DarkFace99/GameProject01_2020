#include "GUI_Array.h"

Srand::GUI_Array::GUI_Array()
{
	m_vector.clear();
	m_interactable.clear();
	m_index = 0;
	m_vectorIndex = 0;
	name = "";
	m_activate = true;
}
Srand::GUI_Array::GUI_Array(std::string name)
{
	m_vector.clear();
	m_interactable.clear();
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

	if (selector != nullptr) { 
		selector->Move();
		selector->gameObject->Update();
	}
	

	if (m_activate && m_inControl)
	{
		bool isButton = m_interactable[m_index]->HasComponent<GUI_Button>();
		if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().OnSelect(); }
		else { m_interactable[m_index]->GetComponent<GUI_Slider>().OnSelect(); }

		if (!levelSelect)
		{
			if (input.IsKeyPressed(SR_KEY_UP) && !isUpPressed)
			{
				if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().DeSelect(); }
				else { m_interactable[m_index]->GetComponent<GUI_Slider>().DeSelect(); }
				m_index = Abs((m_index - 1) % m_interactable.size());
				isUpPressed = true;
				SR_TRACE("Index: {0}", m_index);
			}
			else if (input.IsKeyPressed(SR_KEY_DOWN) && !isDownPressed)
			{
				if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().DeSelect(); }
				else { m_interactable[m_index]->GetComponent<GUI_Slider>().DeSelect(); }
				m_index = Abs((m_index + 1) % m_interactable.size());
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
			else if (input.IsKeyPressed(SR_KEY_Z)) {} // delay for next scene
			
		}
		else 
		{
			if (input.IsKeyPressed(SR_KEY_LEFT) && !isLeftPressed)
			{
				if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().DeSelect(); }
				else { m_interactable[m_index]->GetComponent<GUI_Slider>().DeSelect(); }
				m_index = Abs((m_index - 1) % m_interactable.size());
				isLeftPressed = true;
				SR_TRACE("Index: {0}", m_index);
			}
			else if (input.IsKeyPressed(SR_KEY_RIGHT) && !isRightPressed)
			{
				if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().DeSelect(); }
				else { m_interactable[m_index]->GetComponent<GUI_Slider>().DeSelect(); }
				m_index = Abs((m_index + 1) % m_interactable.size());
				isRightPressed = true;
				SR_TRACE("Index: {0}", m_index);
			}
			else if (input.IsKeyReleased(SR_KEY_LEFT) && isLeftPressed)
			{
				//m_index = Abs((m_index - 1) % VectorSize());
				isLeftPressed = false;
				//SR_TRACE("Index: {0}", m_index);
			}
			else if (input.IsKeyReleased(SR_KEY_RIGHT) && isRightPressed)
			{
				//m_index = Abs((m_index + 1) % VectorSize());
				isRightPressed = false;
				//SR_TRACE("Index: {0}", m_index);
			}
			else if (input.IsKeyPressed(SR_KEY_UP) && !isUpPressed)
			{
				if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().DeSelect(); }
				else { m_interactable[m_index]->GetComponent<GUI_Slider>().DeSelect(); }
				if (m_index - 6 < 0) 
				{
					
				}
				else 
				{
					m_index = Abs((m_index - 6) % m_interactable.size());
				}
				isUpPressed = true;
				SR_TRACE("Index: {0}", m_index);
			}
			else if (input.IsKeyPressed(SR_KEY_DOWN) && !isDownPressed)
			{
				if (isButton) { m_interactable[m_index]->GetComponent<GUI_Button>().DeSelect(); }
				else { m_interactable[m_index]->GetComponent<GUI_Slider>().DeSelect(); }
				if(m_index + 6 > 11)
				{
					
				}
				else 
				{
					m_index = Abs((m_index + 6) % m_interactable.size());
				}
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
			else if (input.IsKeyPressed(SR_KEY_Z)) {} // delay for next scene
		}

		/* Activate key */
		if (input.IsKeyPressed(SR_KEY_SPACE) && isButton && !isSpacePressed)
		{
			m_interactable[m_index]->GetComponent<GUI_Button>().OnActivate();
			isSpacePressed = true;
		}
		else if (input.IsKeyReleased(SR_KEY_SPACE) && isButton && isSpacePressed)
		{
			isSpacePressed = false;
		}
	}
}
void Srand::GUI_Array::Clear()
{
	m_vector.clear();
	m_interactable.clear();
	m_index = 0;
	m_vectorIndex = 0;
	name.clear();
	m_activate = true;
}

void Srand::GUI_Array::Override(_FUNC func)
{
	m_overrideFunc = func;
}

void Srand::GUI_Array::ResetOverride()
{
	m_overrideFunc = nullptr;
}

void Srand::GUI_Array::PushGUI(GameObject* gui)
{
	m_vector.emplace(m_vector.begin() + m_vectorIndex, gui);
	/*m_vector[m_vectorIndex]->GetComponent<GUI_Button>().SetIndex(m_vectorIndex);*/
	m_vectorIndex++;

	if (gui->HasComponent<GUI_Button>() || gui->HasComponent<GUI_Slider>()) {
		m_interactable.push_back(gui);
	}
}

