#pragma once

#include <srpch.h>
#include <vector>
#include "ECS/GameObject.h"
#include "ecspch.h"
#include "Source/GUI_Array.h"

class UI_Box : public Component
{
private:
	GUI_Array* gui_arr = nullptr;
	bool isActive = false;
	std::vector<GameObject*> list;

public:
	UI_Box() = default;
	virtual ~UI_Box() = default;

	void Attach(GUI_Array* gui_arr) {
		this->gui_arr = gui_arr;
	}

	void Add(GameObject* ganeObject) {
		list.push_back(ganeObject);
	}

	void SetRender(bool con) {
		for (int i = 0; i < list.size(); i++) {
			if (con) { list[i]->GetComponent<SpriteRenderer>().SetAlpha(1.0f); }
			else{ list[i]->GetComponent<SpriteRenderer>().SetAlpha(0.0f); }
		}
	}

	inline void SetAttach(bool con) { 
		SetRender(con);
		gui_arr->SetControl(con); 
	}

	inline void Chosen(bool state) {
		SetRender(state);
	}
};