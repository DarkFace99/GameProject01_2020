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

void Srand::GUI_Button::SelectedOffset(int x, int y) {
	tileSelector = &gameObject->GetComponent<TileSelector>();
	originX = tileSelector->GetOffset().x;
	originY = tileSelector->GetOffset().y;
	shiftX = x;
	shiftY = y;
	isShifted = true;
}

void Srand::GUI_Button::OnSelect()
{
	SR_TRACE("Button {0}: Selected", name);
	if (!isSelected && isShifted) {
		isSelected = true;
		tileSelector->SetTile(shiftX, shiftY);
	}
	
}

void Srand::GUI_Button::DeSelect()
{
	if (isShifted) {
		isSelected = false;
		tileSelector->SetTile(originX, originY);
	}
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
