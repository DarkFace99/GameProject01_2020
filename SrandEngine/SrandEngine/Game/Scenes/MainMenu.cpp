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

#pragma region UI_Button

    // button1
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((14 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7*16 * RATIO, 2*16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(1, 16);

    tempgui->AddComponent<GUI_Button>("PlayButton");
    tempgui->GetComponent<GUI_Button>().m_function = StartGame;
    
    gui_arr.PushGUI(tempgui);

    // button2
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((11 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(1, 16);

    tempgui->AddComponent<GUI_Button>("PlayButton");
    tempgui->GetComponent<GUI_Button>().m_function = StartGame;

    gui_arr.PushGUI(tempgui);

    // button3
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((8 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(1, 16);

    tempgui->AddComponent<GUI_Button>("PlayButton");
    tempgui->GetComponent<GUI_Button>().m_function = StartGame;

    gui_arr.PushGUI(tempgui);

    // button4
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(1, 16);

    tempgui->AddComponent<GUI_Button>("PlayButton");
    tempgui->GetComponent<GUI_Button>().m_function = StartGame;

    gui_arr.PushGUI(tempgui);

#pragma endregion

#pragma region TEXT

    // Play
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((10 * _tileSize) + _midPointX) * RATIO, ((14 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(6 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_WORD6_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(0, 14);

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