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
    std::vector<glm::vec4> tile_info;
    GameObject* tempgui = nullptr;

    /* BACKGROUND */
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(0 * RATIO, 0 * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(480 * RATIO, 270 * RATIO);

        gameObject->AddComponent<SpriteRenderer>("BG_MESH", "BG_TEX", 1.0f, &camera, false);
    }

#pragma region TileSet

    for (int i = 0; i < 30; i++) {
        tile_info.push_back(glm::vec4(i, 0, 2, 6));
    }

    for (int i = 15; i < 21; i++) {
        if      (i == 15) {     tile_info.push_back(glm::vec4(i, 3, 1, 2)); }
        else if (i == 20) {     tile_info.push_back(glm::vec4(i, 3, 3, 2)); }
        else {                  tile_info.push_back(glm::vec4(i, 3, 2, 2)); }
    }
    tile_info.push_back(glm::vec4(24, 3, 6, 2));
    tile_info.push_back(glm::vec4(28, 3, 6, 2));

    for (int i = 0; i < tile_info.size(); i++)
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((_midPointX + _offset + (tile_info[i].x * _tileSize)) * RATIO, (_midPointY + _offset + (tile_info[i].y * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::TILE_LAYER, "TILESET_MESH", "TILESET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(8, 8);

        gameObject->GetComponent<TileSelector>().SetTile(tile_info[i].z, tile_info[i].w);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::TILE_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y);

        objManager.PushObject(gameObject);
    }
#pragma endregion

#pragma region GUI_LOADING

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

#pragma endregion
}

void MainMenu::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
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