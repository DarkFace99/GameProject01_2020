#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "Component.h"
#include "Transform.h"

constexpr float GRAVITY = 9.81f;

class RigidBody : public Component 
{
private:
	float gravityScale = 1.0f;
	Vector2D_float drag = Vector2D_float();
	Vector2D_float force = Vector2D_float();

	Vector2D_float velocity = Vector2D_float();
	Transform* transform = nullptr;

public:
	RigidBody() = default;
	virtual ~RigidBody() = default;

	RigidBody(float gravity_scale) : gravityScale(gravity_scale) {}

	bool Init() override final 
	{
		return true;
	}

	void Update() override final 
	{
		transform = &gameObject->GetComponent<Transform>();

		velocity.x = force.x - drag.x;
		velocity.y = force.x + drag.y + -(gravityScale * GRAVITY);
		transform->Translate(velocity);
	}

	void SetForce(const Vector2D_float force) 
	{
		this->force = force;
	}

};
