#include "MainMenu.h"

MainMenu::MainMenu() :Scene("MainMenu")
{}

MainMenu::~MainMenu()
{
	Clean();
}

void StartGame() { Engine::get().GoToScene(1); }


void MainMenu::Init()
{
	manager = &EntityManager::get();
    GameObject* tempgui = nullptr;

    tempgui = new GameObject();
    //EntityManager::get().AddEntity(tempgui);

    tempgui->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "B_MESH", "B_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<GUI_Button>("TestButton1");
    tempgui->GetComponent<GUI_Button>().m_function = StartGame;
    gui_arr.PushGUI(tempgui);

    tempgui = new GameObject();
    //EntityManager::get().AddEntity(tempgui);

    tempgui->AddComponent<Transform>(0, 100);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "B_MESH", "B_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<GUI_Button>("TestButton2");

    gui_arr.PushGUI(tempgui);
}

void MainMenu::Clean()
{
    manager->Clean();
    audioController.Stop();
    gui_arr.Clear();
}

void MainMenu::Draw()
{
    manager->Draw();
    gui_arr.OnDraw();
}

void MainMenu::Update()
{
    manager->Update();
    gui_arr.OnUpdate();
}