#include "LevelSelect.h"

LevelSelect::LevelSelect() :Scene("LevelSelect")
{}

LevelSelect::~LevelSelect()
{
    Clean();
}

void LevelSelect::Init()
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
        tile_info.push_back(glm::vec4(i, 0, 2, 5));
    }

    for (int i = 0; i < 30; i++) {
        tile_info.push_back(glm::vec4(i, 1, 2, 6));
    }

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

#pragma region Title
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((12 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(14 * 16 * RATIO, 3 * 16 * RATIO);

    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SELECT_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(22, 22);
    gameObject->GetComponent<TileSelector>().SetTile(1, 8);
#pragma endregion

#pragma region UI_Button
    // button
    for (int i = 0; i < 12; i++) {
        if (i < progress) {
            tempgui = new GameObject();
            tempgui->GetComponent<Transform>().position = Vector2D_float(((((i * 2 % 12) + 10) * _tileSize) + _midPointX) * RATIO, (((i < 6 ? 7.5f : 5.5f) * _tileSize) + _midPointY) * RATIO);
            tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

            tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
            tempgui->AddComponent<TileSelector>(22, 22);
            tempgui->GetComponent<TileSelector>().SetTile(7, 19);

            tempgui->AddComponent<GUI_Button>("Button");
            tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);
        }
        else {
            tempgui = new GameObject();
            tempgui->GetComponent<Transform>().position = Vector2D_float(((((i * 2 % 12) + 10) * _tileSize) + _midPointX) * RATIO, (((i < 6 ? 7.5f : 5.5f) * _tileSize) + _midPointY) * RATIO);
            tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

            tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
            tempgui->AddComponent<TileSelector>(22, 22);
            tempgui->GetComponent<TileSelector>().SetTile(1, 16);

            tempgui->AddComponent<GUI_Text>("Lock");
        }

        gui_arr.PushGUI(tempgui);
    }

    // num
    for (int i = 0; i < progress; i++) {

        tempgui = new GameObject();
        tempgui->GetComponent<Transform>().position = Vector2D_float(((((i * 2 % 12) + 10.5) * _tileSize) + _midPointX) * RATIO, (((i < 6 ? 8 : 6) * _tileSize) + _midPointY) * RATIO);
        tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        tempgui->AddComponent<TileSelector>(22, 22);
        tempgui->GetComponent<TileSelector>().SetTile((i * 2 % 16) + 1, (i < 8 ? 14 : 12));

        tempgui->AddComponent<GUI_Text>("Number");

        gui_arr.PushGUI(tempgui);
    }



    {
        //// button2
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((12 * _tileSize) + _midPointX) * RATIO, ((7.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV2");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button3
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((14 * _tileSize) + _midPointX) * RATIO, ((7.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV3");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button4
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((16 * _tileSize) + _midPointX) * RATIO, ((7.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV4");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button5
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((18 * _tileSize) + _midPointX) * RATIO, ((7.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV5");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button6
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((20 * _tileSize) + _midPointX) * RATIO, ((7.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV6");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button7
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((10 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV7");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button8
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((12 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV8");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button9
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((14 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV9");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button10
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((16 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV10");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button11
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((18 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV11");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);

        //// button12
        //tempgui = new GameObject();
        //tempgui->GetComponent<Transform>().position = Vector2D_float(((20 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
        //tempgui->AddComponent<TileSelector>(22, 22);
        //tempgui->GetComponent<TileSelector>().SetTile(7, 19);

        //tempgui->AddComponent<GUI_Button>("LV12");
        //tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 19);

        //gui_arr.PushGUI(tempgui);
    }

#pragma endregion
}

void LevelSelect::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    audioController.Stop();
    gui_arr.Clear();
}

void LevelSelect::Draw()
{
    manager->Draw();
    gui_arr.OnDraw();
}

void LevelSelect::Update()
{
    manager->Update();
    gui_arr.OnUpdate();
}