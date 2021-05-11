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
	//steps.clear();
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
	//SR_TRACE("Slider {0}: Selected", name);
	if (!isSelected) {
		isSelected = true;
		if (isConcealed) { renderer->SetAlpha(1.0f); }
	}
	if (isSelected) { AdjustStep(); }
	
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

void Srand::GUI_Slider::AdjustStep() {
	if (input.IsKeyPressed(SR_KEY_RIGHT) && !isRightPressed)
	{
		isRightPressed = true;
		if (m_function != nullptr) { m_function(); }
	}
	else if (input.IsKeyPressed(SR_KEY_LEFT) && !isLeftPressed)
	{
		isLeftPressed = true;
		if (n_function != nullptr) { n_function(); }
	}
	else if (input.IsKeyReleased(SR_KEY_RIGHT) && isRightPressed)
	{
		//m_index = Abs((m_index - 1) % VectorSize());
		isRightPressed = false;
		//SR_TRACE("Index: {0}", m_index);
	}
	else if (input.IsKeyReleased(SR_KEY_LEFT) && isLeftPressed)
	{
		//m_index = Abs((m_index + 1) % VectorSize());
		isLeftPressed = false;
		//SR_TRACE("Index: {0}", m_index);
	}
}

void Srand::GUI_Slider::ChangeStep(int num){
	if (num == 0 && currentStep != 0) { // decrement
		currentStep--;
		if (currentStep < 0) { currentStep = 0; }
		steps[currentStep]->GetComponent<SpriteRenderer>().SetAlpha(0.0f);
	}
	else if(num == 1 && currentStep != steps.size()){ // increment
		steps[currentStep]->GetComponent<SpriteRenderer>().SetAlpha(1.0f);
		currentStep++;
		if (currentStep > steps.size()) { currentStep = steps.size(); }
	}
}

void Srand::GUI_Slider::JumpStep(int num)
{
	currentStep = num;

	for (int i = 0; i < steps.size(); i++)
	{
		if (i < num) 
		{
			steps[i]->GetComponent<SpriteRenderer>().SetAlpha(1.0f);
		}
		else if (i >= num)
		{
			steps[i]->GetComponent<SpriteRenderer>().SetAlpha(0.0f);
		}
	}
}
