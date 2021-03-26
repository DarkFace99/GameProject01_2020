#pragma once

#include "GameObject.h"
#include "Source/Vector2D.h"
#include "Component.h"
#include "Transform.h"

constexpr float GRAVITY = 9.81f;

class RigidBody : public Component 
{
private:
	float gravityScale = 1.0f;
	Vector2D_float drag = Vector2D_float(3.0f, 0.0f);
	float dragX_Value = 0.88f;
	Vector2D_float force = Vector2D_float();

	Vector2D_float velocity = Vector2D_float();
	Transform* transform = nullptr;

public:
	RigidBody() : gravityScale(1.0f) {}
	virtual ~RigidBody() = default;

	RigidBody(float gravity_scale) : gravityScale(gravity_scale) {}

	bool Init() override final 
	{
		transform = &gameObject->GetComponent<Transform>();
		return true;
	}

	void Update() override final 
	{
		//velocity.x = (force.x - drag.x) * Srand::TimeStep::get();
		//velocity.y += (force.x + drag.y + -(gravityScale * GRAVITY)) * Srand::TimeStep::get();
		//if (velocity.y < -20) { velocity.y = -20; } // hard code
	}

	void SetForce(const Vector2D_float force) 
	{
		this->force = force;
	}

	void SetVelocityX(float v_X) {
		velocity.x = v_X;
	}

	void SetVelocityY(float v_Y) {
		velocity.y = v_Y;
	}

	float GetVelocityY() 
	{
		return velocity.y;
	}
	float GetVelocityX() 
	{
		return velocity.x;
	}

	Vector2D_float GetVelocity()
	{
		return velocity;
	}

	void Update_Gravity() {
		//velocity.x += (force.x - drag.x) * Srand::TimeStep::get();
		velocity.x *= dragX_Value;
		velocity.y += (force.x + drag.y + -(gravityScale * GRAVITY)) * Srand::TimeStep::get();
		if (velocity.y < -20) { velocity.y = -20; } // hard code
		if (abs(velocity.x) < 0.01f) { velocity.x = 0; }
	}
};
