#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class Lv3 : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;
public:
	Lv3();
	~Lv3();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;
};
