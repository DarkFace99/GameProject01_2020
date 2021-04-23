#include "GUI_Slider.h"

Srand::GUI_Slider::GUI_Slider()
{
	SetType(Type::SLIDER);
}
Srand::GUI_Slider::GUI_Slider(std::string name)
	: name(name)
{
	SetType(Type::SLIDER);
}
Srand::GUI_Slider::~GUI_Slider()
{

}

void Srand::GUI_Slider::OnSelect()
{
	SR_TRACE("Slider {0}: Selected", name);
}
void Srand::GUI_Slider::OnActivate()
{
	SR_TRACE("Slider {0}: Activated", name);

}
