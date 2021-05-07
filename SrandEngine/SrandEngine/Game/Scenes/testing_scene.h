#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class TestingScene : public Srand::Scene 
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;
public:
	TestingScene();
	~TestingScene();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;
};
