#include "GUI_Button.h"

Srand::GUI_Button::GUI_Button()
{
	SetType(Type::BUTTON);
}
Srand::GUI_Button::GUI_Button(std::string name)
	: name(name)
{
	SetType(Type::BUTTON);
}
Srand::GUI_Button::~GUI_Button()
{

}

bool Srand::GUI_Button::Init()
{
	Initialize();
	return true;
}

void Srand::GUI_Button::Update()
{
	OnSelect();
}
void Srand::GUI_Button::OnSelect()
{
	SR_TRACE("Button {0}: Selected", name);
}
void Srand::GUI_Button::OnActivate()
{
	SR_TRACE("Button {0}: Activated", name);
	if(m_function != nullptr){ m_function(); }
}

void Srand::GUI_Button::SetIndex(int i)
{
	currentIndex = i;
}

int Srand::GUI_Button::GetIndex()
{
	return currentIndex;
}
