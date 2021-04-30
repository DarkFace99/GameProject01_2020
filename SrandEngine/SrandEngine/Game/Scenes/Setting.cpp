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

#pragma region BOARD
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((8.5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(20 * 16 * RATIO, 13 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BOARD_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(1, 8);

    tempgui->AddComponent<GUI_Text>("BOARD");
    gui_arr.PushGUI(tempgui);

    //Slot1
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((12.65 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT1");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);

    //Slot2
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((11.20 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT2");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);

    //Slot3
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((9.75 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT3");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);

    //Slot4
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((8.3 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT4");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);
    
    //default

    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((3.5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(6 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_DEFAULT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(22, 22);
    tempgui->GetComponent<TileSelector>().SetTile(1, 6);

    tempgui->AddComponent<GUI_Button>("Default");
    tempgui->GetComponent<GUI_Button>().SelectedOffset(7, 6);
    gui_arr.PushGUI(tempgui);
#pragma endregion

}

void Setting::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    audioController.Stop();
    gui_arr.Clear();
}

void Setting::Draw()
{
    manager->Draw();
    gui_arr.OnDraw();
}

void Setting::Update()
{
    manager->Update();
    gui_arr.OnUpdate();
}
