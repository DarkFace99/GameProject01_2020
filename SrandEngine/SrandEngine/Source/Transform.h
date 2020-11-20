#pragma once

#include "Component.h"
#include "Vector2D.h"

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

	void Translate(const Vector2D_float v) {
		position += v;
	}

	virtual ~Transform() = default;

	Vector2D_float position = Vector2D_float(0, 0);
	Vector2D_float scale = Vector2D_float(1, 1);

	float rotationAngle = 0.0f;
};