#pragma once

#include "Component.h"
#include "Source/Vector2D.h"
#include "Source/TimeStep.h"

class Transform : public Component
{
public:
	Transform() = default;

	Transform(float pos_x, float pos_y)
	{
		position.Set_XY(pos_x, pos_y);
	}
	Transform(float pos_x, float pos_y, float scale_x, float scale_y)
	{
		position.Set_XY(pos_x, pos_y);
		scale.Set_XY(scale_x, scale_y);
	}
	Transform(float pos_x, float pos_y, float scale_x, float scale_y, float rotation)
	{
		position.Set_XY(pos_x, pos_y);
		scale.Set_XY(scale_x, scale_y);
		rotationAngle = rotation;
	}

	void Translate(Vector2D_float v) 
	{
		this->position += v;
	}
	void SetPosition(Vector2D_float p) 
	{
		this->position = p;
	}

	virtual ~Transform() = default;

	Vector2D_float position = Vector2D_float(0, 0);
	Vector2D_float scale = Vector2D_float(1, 1);

	float rotationAngle = 0.0f;
};