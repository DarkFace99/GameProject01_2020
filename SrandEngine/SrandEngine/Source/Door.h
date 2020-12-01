#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider2D.h"

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
		
	}

	/*void AddConnectedButtons(GameObject* _gameObj) 
	{
		if (_gameObj->HasComponent<Button>()) 
		{
			connectedButtons.push_back(_gameObj);
		}
		else 
		{
			std::cout << "This Object do not have Button Component" << std::endl;
		}
	}*/
	void MoveDoor(Vector2D_float v) 
	{
		Vector2D_float* tempPos = &gameObject->GetComponent<Transform>().position;
		gameObject->GetComponent<Transform>().Translate(v);
	}

};
