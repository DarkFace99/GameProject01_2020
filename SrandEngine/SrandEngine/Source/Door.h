#pragma once

#include "Engine.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider2D.h"
#include "Button.h"

//class Button;

class Door : public Component 
{
private:
	Transform* transform = nullptr;
	BoxCollider2D* collider = nullptr;

	std::vector<GameObject*> connectedButtons;

public:
	Door() = default;
	virtual ~Door() = default;

	bool Init() override final
	{
		transform = &gameObject->GetComponent<Transform>();
		collider = &gameObject->GetComponent<BoxCollider2D>();
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
		for (int i = 0; i < connectedButtons.size(); i++) 
		{
			if (connectedButtons[i]->GetComponent<Button>().CheckCollideActivate()) 
			{
				collider->SetOverlap(true);
				std::cout << collider->GetOverlap() << std::endl;
			}
			else
			{
				collider->SetOverlap(false);
				std::cout << collider->GetOverlap() << std::endl;
			}
		}
	}

};
