#pragma once

#include <vector>
#include "Source/Engine.h"

#include "ecspch.h"
#include "Button.h"

class Elevator : public Component 
{
private:
	int elevatedHeight = 0;

	Transform* transform = nullptr;
	BoxCollider2D* collider = nullptr;

	Vector2D_float max_height = Vector2D_float();
	Vector2D_float ground_height = Vector2D_float();

	float max_elevation = 0.0f;
	float ground_elevation = 0.0f;

	int activeValue = 0;

	std::vector<GameObject*> connectedButtons;

public:
	Elevator(int elevatedHeight) : elevatedHeight(elevatedHeight) {}
	virtual ~Elevator() = default;

	bool Init() override final 
	{
		transform = &gameObject->GetComponent<Transform>();
		collider = &gameObject->GetComponent<BoxCollider2D>();

		max_elevation = transform->position.y + elevatedHeight;
		ground_elevation = transform->position.y;

		max_height = Vector2D_float(transform->position.x, max_elevation);
		ground_height = transform->position;

		return true;
	}
	void Draw() override final 
	{
		
	}
	void Update() override final 
	{
		Elevated();
	}

	void AddConnectedButtons(GameObject* _gameObj)
	{
		if (!_gameObj->HasComponent<Button>())
		{
			std::cout << "Button: <BoxCollider2D> component is not found." << std::endl;
		}
		else
		{
			connectedButtons.push_back(_gameObj);
		}
	}
	void Elevated() 
	{
		activeValue = 0;

		for (int i = 0; i < connectedButtons.size(); i++)
		{

			if (connectedButtons[i]->GetComponent<Button>().CheckCollideActivate())
			{
				activeValue++;
			}

			/*if (connectedButtons[i]->GetComponent<Button>().CheckCollideActivate())
			{
				transform->Translate(Vector2D_float(0.0f, 1.0f));
				if (transform->position.y > max_elevation) { transform->SetPosition(max_height); }
			}
			else
			{
				transform->Translate(Vector2D_float(0.0f, -1.0f));
				if (transform->position.y <= ground_elevation) { transform->SetPosition(ground_height); }
			}*/
		}

		if (activeValue % 2 != 0)
		{
			transform->Translate(Vector2D_float(0.0f, 1.0f));
			if (transform->position.y > max_elevation) { transform->SetPosition(max_height); }
		}
		else
		{
			transform->Translate(Vector2D_float(0.0f, -1.0f));
			if (transform->position.y <= ground_elevation) { transform->SetPosition(ground_height); }
		}
	}

};