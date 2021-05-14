#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class Level2 : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;
public:
	Level2();
	~Level2();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;
};
