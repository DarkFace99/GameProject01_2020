#include "GUI_Text.h"

Srand::GUI_Text::GUI_Text()
{
	SetType(Type::TEXT);
}
Srand::GUI_Text::GUI_Text(std::string name)
	: name(name)
{
	SetType(Type::TEXT);
}
Srand::GUI_Text::~GUI_Text()
{

}

bool Srand::GUI_Text::Init()
{
	Initialize();
	return true;
}


