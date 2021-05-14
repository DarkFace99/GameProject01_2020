#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class Level3 : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;
public:
	Level3();
	~Level3();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;
};

