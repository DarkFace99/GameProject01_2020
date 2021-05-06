#include "GUI_Selector.h"

Srand::GUI_Selector::GUI_Selector()
{
	SetType(Type::SELECTOR);
}
Srand::GUI_Selector::GUI_Selector(std::string name)
	: name(name)
{
	SetType(Type::SELECTOR);
}
Srand::GUI_Selector::~GUI_Selector()
{

}

bool Srand::GUI_Selector::Init()
{
	Initialize();
	return true;
}

void Srand::GUI_Selector::AttachOrigin(Transform* transform) { origin = transform; }
void Srand::GUI_Selector::SetDestination(Transform* transform) { destination = transform; }
void Srand::GUI_Selector::IsChoosing(bool con) { activate = con; }

void Srand::GUI_Selector::Move() {
	if (activate) {
		renderer->SetAlpha(1.0f);
		transform->SetPosition(Vector2D_float(destination->position.x, destination->position.y));
	}
	else {
		renderer->SetAlpha(0.0f);
		transform->SetPosition(Vector2D_float(origin->position.x, origin->position.y));
	}
}
