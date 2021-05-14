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

void Srand::GUI_Button::Conceal() {
	isConcealed = true;
	renderer->SetAlpha(0.0f);
}

void Srand::GUI_Button::OnSelect()
{
	//SR_TRACE("Button {0}: Selected", name);
	if (!isSelected && isShifted) {
		isSelected = true;
		tileSelector->SetTile(shiftX, shiftY);
	}
	else if (!isSelected && isConcealed) {
		isSelected = true;
		renderer->SetAlpha(1.0f);
	}
	
}

void Srand::GUI_Button::DeSelect()
{
	isSelected = false;
	if (isShifted) {	
		tileSelector->SetTile(originX, originY);
	}if (isConcealed) { renderer->SetAlpha(0.0f); }
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

void Srand::GUI_Button::AttachObj(GameObject* obj) { attachedObj = obj; }
void Srand::GUI_Button::SetAttach(bool state) { attachedObj->GetComponent<SpriteRenderer>().SetAlpha(state ? 1.0f : 0.0f); }