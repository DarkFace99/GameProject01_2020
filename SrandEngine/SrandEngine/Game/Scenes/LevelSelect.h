#pragma once

#include "Source/EntityManager.h"
#include "Source/Scene.h"

class LevelSelect : public Srand::Scene
{
private:
	EntityManager* manager = nullptr;
	GUI_Array gui_arr;
	// for testing
	int progress;
	WindowsInput input;

public:
	
	LevelSelect();
	~LevelSelect();

	virtual void Init() override;
	virtual void Clean() override;
	virtual void Draw() override;
	virtual void Update() override;

	inline void SetProgress(int proc) { progress = proc; }
	inline int GetProgress() { return progress; }
};