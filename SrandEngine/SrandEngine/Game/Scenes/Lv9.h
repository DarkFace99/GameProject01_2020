#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class Lv9 : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;

public:
	Lv9();
	~Lv9();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;
};