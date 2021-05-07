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
	animator = &gameObject->GetComponent<Animator>();
	return true;
}

void Srand::GUI_Selector::AttachOrigin(Transform* transform) { origin = transform; }
void Srand::GUI_Selector::SetDestination(Transform* transform) { destination = transform; }
void Srand::GUI_Selector::IsActive(bool con) { activate = con; }
void Srand::GUI_Selector::SetOffset(float x, float y) {
	xOffset = x;
	yOffset = y;
	offsetEnable = true;
}

void Srand::GUI_Selector::Move() {
	if (activate) {
		
		renderer->SetAlpha(1.0f);
		float chaseX;
		float chaseY;
		if (offsetEnable) {
			chaseX = transform->position.x + 0.1f * (destination->position.x + xOffset - transform->position.x);
			chaseY = transform->position.y + 0.1f * (destination->position.y + yOffset - transform->position.y);
		}
		else {
			chaseX = transform->position.x + 0.1f * (destination->position.x - transform->position.x);
			chaseY = transform->position.y + 0.1f * (destination->position.y - transform->position.y);
		}
		transform->SetPosition(Vector2D_float(chaseX, chaseY));

		// State
		if (percentRange <= 0.7) {}
		else if (percentRange <= 0.9) {}
		else {}
	}
	else if(!activate){
		offsetEnable = false;
		renderer->SetAlpha(0.0f);
		transform->SetPosition(Vector2D_float(origin->position.x, origin->position.y));
	}
}

void Srand::GUI_Selector::SetPercentRange(float percent) { percentRange = percent; }
