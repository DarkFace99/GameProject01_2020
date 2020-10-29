#pragma once

class GameObject;

class Component {
public:
	Component() = default;
	virtual ~Component() = default;

	GameObject* gameObject; // The game object that this component will be attached

	virtual bool Init() { return true; }
	virtual void Draw() {}
	virtual void Update() {}
};
