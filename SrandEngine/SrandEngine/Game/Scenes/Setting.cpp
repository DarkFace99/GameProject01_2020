#include "Setting.h"

Setting::Setting()
	: Scene("Setting")
{}
Setting::~Setting()
{
	Clean();
}

void Setting::Init()
{
	manager = &EntityManager::get();
	GameObject* tempgui = nullptr;
}
void Setting::Clean()
{

}
void Setting::Draw()
{

}
void Setting::Update()
{

}
