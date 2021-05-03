#pragma once

#include <srpch.h>
#include "ecspch.h"
#include "Source/GUI_Array.h"

class UI_Box : public Component
{
private:
	GUI_Array* gui_arr = nullptr;
	bool isActive = false;

public:
	UI_Box() = default;
	virtual ~UI_Box() = default;

	void Attach(GUI_Array* gui_arr) {
		this->gui_arr = gui_arr;
	}

	inline void SetActive(bool con) { isActive = con; }
};