#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class EndLevel : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;

	Transform* macho = nullptr;
	Transform* cherry = nullptr;
	Transform* pear = nullptr;
	Transform* barter = nullptr;

public:
	EndLevel();
	~EndLevel();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;
};
