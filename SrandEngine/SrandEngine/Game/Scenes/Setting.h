#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class Setting : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;

	/*float saved_volM = 1.0f;
	float saved_volE = 1.0f;
	bool saved_isFull = false;*/

public:
	Setting();
	~Setting();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;

};

