#include "MainMenu.h"

MainMenu::MainMenu() :Scene("MainMenu")
{}

MainMenu::~MainMenu()
{
	Clean();
}

void MainMenu::Init()
{
	manager = &EntityManager::get();
}

void MainMenu::Clean()
{
    manager->Clean();
    audioController.Stop();
}

void MainMenu::Draw()
{
    manager->Draw();
}

void MainMenu::Update()
{
    manager->Update();
}