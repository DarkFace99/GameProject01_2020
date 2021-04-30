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

#pragma region TileSet

    tile_info.push_back(glm::vec4(3, 1, 1, 2));
    for (int i = 0; i < 2; i++) {
        tile_info.push_back(glm::vec4(i+4, 1, 2, 2));
    }
    tile_info.push_back(glm::vec4(6, 1, 3, 2));

    tile_info.push_back(glm::vec4(26, 1, 1, 2));
    tile_info.push_back(glm::vec4(27, 1, 3, 4));

    for (int i = 0; i < 3; i++) {
        tile_info.push_back(glm::vec4(27, i+2, 6, 5));
    }
    tile_info.push_back(glm::vec4(27, 4, 6, 6));
    tile_info.push_back(glm::vec4(1, 4, 6, 2));
    

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

    //sign
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((27.5 * _tileSize) + _midPointX) * RATIO, ((5.75 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

    gameObject->AddComponent<SpriteRenderer>("2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(14, 14);
    gameObject->GetComponent<TileSelector>().SetTile(7, 11);

    // button
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((5 * _tileSize) + _midPointX) * RATIO, ((2.5 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 1 * 16 * RATIO);

    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(14, 14);
    gameObject->GetComponent<TileSelector>().SetTile(1, 3);

    // Door
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((1.5 * _tileSize) + _midPointX) * RATIO, ((7 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 64.0f * RATIO);

    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(14, 14);
    gameObject->GetComponent<TileSelector>().SetTile(1, 9);

    //stand
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((1.5 * _tileSize) + _midPointX) * RATIO, ((4.5 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);

    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(14, 14);
    gameObject->GetComponent<TileSelector>().SetTile(1, 7);

#pragma region BOARD
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((8.5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(20 * 16 * RATIO, 13 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BOARD_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(44, 44);
    tempgui->GetComponent<TileSelector>().SetTile(2, 17);

    tempgui->AddComponent<GUI_Text>("BOARD");
    gui_arr.PushGUI(tempgui);

    //Slot1
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((12.60 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(44, 44);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT1");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);

    //Slot2
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((11.10 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(44, 44);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT2");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);

    //Slot3
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((9.60 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(44, 44);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT3");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);

    //Slot4
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((8.10 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(44, 44);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("SLOT4");
    tempgui->GetComponent<GUI_Button>().Conceal();
    gui_arr.PushGUI(tempgui);
    
    //default

    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((3 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(5 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_DEFAULT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(44, 44);
    tempgui->GetComponent<TileSelector>().SetTile(3, 13);

    tempgui->AddComponent<GUI_Button>("Default");
    tempgui->GetComponent<GUI_Button>().SelectedOffset(15, 13);
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
