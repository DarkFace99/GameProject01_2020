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

void Srand::GUI_Button::OnSelect()
{
	SR_TRACE("Button {0}: Selected", name);
}
void Srand::GUI_Button::OnActivate()
{
	SR_TRACE("Button {0}: Activated", name);
}
