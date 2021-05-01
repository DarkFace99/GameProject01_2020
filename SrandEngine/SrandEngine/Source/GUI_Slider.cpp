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
	step.clear();
}

bool Srand::GUI_Slider::Init()
{
	Initialize();
	return true;
}

void Srand::GUI_Slider::Update()
{
	OnSelect();
}

void Srand::GUI_Slider::Conceal() {
	isConcealed = true;
	renderer->SetAlpha(0.0f);
}

void Srand::GUI_Slider::OnSelect()
{
	SR_TRACE("Slider {0}: Selected", name);
	if(!isSelected && isConcealed) {
		isSelected = true;
		renderer->SetAlpha(1.0f);
	}
}

void Srand::GUI_Slider::DeSelect()
{
	isSelected = false;
	if (isConcealed) { renderer->SetAlpha(0.0f); }
}

void Srand::GUI_Slider::OnActivate()
{
	SR_TRACE("Slider {0}: Activated", name);

}
