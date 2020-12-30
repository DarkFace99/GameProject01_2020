#pragma once

#include "Source/Engine.h"

#include "ecspch.h"
#include "Button.h"

//class Button;

class Door : public Component 
{
private:
	Transform* transform = nullptr;
	BoxCollider2D* collider = nullptr;
	SpriteRenderer* spriteRenderer = nullptr;

	std::vector<GameObject*> connectedButtons;
	bool defaultState = true;
	int activeValue = 0;

public:
	Door() = default;
	virtual ~Door() = default;

	Door(bool defaultState): defaultState(defaultState){}

	bool Init() override final
	{
		transform = &gameObject->GetComponent<Transform>();
		collider = &gameObject->GetComponent<BoxCollider2D>();
		spriteRenderer = &gameObject->GetComponent<SpriteRenderer>();
		return true;
	}
	void Draw() override final
	{
		
	}
	void Update() override final
	{
		OpenDoor();
	}

	void AddConnectedButtons(GameObject* _gameObj) 
	{
		if (!_gameObj->HasComponent<Button>()) 
		{
			std::cout << "Door: <BoxCollider2D> component is not found." << std::endl;
		}
		else 
		{
			connectedButtons.push_back(_gameObj);
		}
	}
	void OpenDoor() 
	{
		activeValue = 0;
		for (int i = 0; i < connectedButtons.size(); i++) 
		{
			if (connectedButtons[i]->GetComponent<Button>().CheckCollideActivate()) {
				activeValue++;
			}
			/*if (connectedButtons[i]->GetComponent<Button>().CheckCollideActivate()) 
			{
				collider->SetOverlap(true);
				std::cout << collider->GetOverlap() << std::endl;
			}
			else
			{
				collider->SetOverlap(false);
				std::cout << collider->GetOverlap() << std::endl;
			}*/
		}

		if (activeValue % 2 != 0) { // true
			if (defaultState) {
				collider->SetOverlap(true);
				spriteRenderer->SetAlpha(0.0f);
			}
			else {
				collider->SetOverlap(false);
				spriteRenderer->SetAlpha(1.0f);
			}
		}
		else {	// false
			if (defaultState) {
				collider->SetOverlap(false);
				spriteRenderer->SetAlpha(1.0f);
			}
			else {
				collider->SetOverlap(true);
				spriteRenderer->SetAlpha(0.0f);
			}
		}
	}

};
