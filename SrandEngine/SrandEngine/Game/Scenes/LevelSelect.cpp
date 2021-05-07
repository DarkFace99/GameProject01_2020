#include "LevelSelect.h"

LevelSelect::LevelSelect() :Scene("LevelSelect")
{}

LevelSelect::~LevelSelect()
{
    Clean();
}

void GoTo_MenuL() { Engine::get().GoToScene(0); }

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

    //sign
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((2 * _tileSize) + _midPointX) * RATIO, ((2.75 * _tileSize) + _midPointY) * RATIO);
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
    gameObject->GetComponent<TileSelector>().SetTile(7, 3);

    // elevator
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((26 * _tileSize) + _midPointX) * RATIO, ((2 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(14, 14);
    gameObject->GetComponent<TileSelector>().SetTile(7, 5);

    //stand 
    // elevator
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((26 * _tileSize) + _midPointX) * RATIO, ((1.5 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 1 * 16 * RATIO);

    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<TileSelector>(14, 14);
    gameObject->GetComponent<TileSelector>().SetTile(7, 4);

#pragma region TileSet

    int tileMAP[16][30] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,
        17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,19
    };

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 30; x++)
        {
            switch (tileMAP[y][x])
            {
            default: printf("empty");
                break;
            case 9: tile_info.push_back(glm::vec4(x, 15 - y, 1, 6));
                break;
            case 10: tile_info.push_back(glm::vec4(x, 15 - y, 2, 6));
                break;
            case 11: tile_info.push_back(glm::vec4(x, 15 - y, 3, 6));
                break;
            case 17: tile_info.push_back(glm::vec4(x, 15 - y, 1, 5));
                break;
            case 18: tile_info.push_back(glm::vec4(x, 15 - y, 2, 5));
                break;
            case 19: tile_info.push_back(glm::vec4(x, 15 - y, 3, 5));
                break;
            case 25: tile_info.push_back(glm::vec4(x, 15 - y, 1, 4));
                break;
            case 26: tile_info.push_back(glm::vec4(x, 15 - y, 2, 4));
                break;
            case 27: tile_info.push_back(glm::vec4(x, 15 - y, 3, 4));
                break;
            case 14: tile_info.push_back(glm::vec4(x, 15 - y, 6, 6));
                break;
            case 22: tile_info.push_back(glm::vec4(x, 15 - y, 6, 5));
                break;
            case 30: tile_info.push_back(glm::vec4(x, 15 - y, 6, 4));
                break;
            case 41: tile_info.push_back(glm::vec4(x, 15 - y, 1, 2));
                break;
            case 42: tile_info.push_back(glm::vec4(x, 15 - y, 2, 2));
                break;
            case 43: tile_info.push_back(glm::vec4(x, 15 - y, 3, 2));
                break;
            case 46: tile_info.push_back(glm::vec4(x, 15 - y, 6, 2));
                break;
            }
        }
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
    gameObject->AddComponent<TileSelector>(25, 25);
    gameObject->GetComponent<TileSelector>().SetTile(1, 11);
#pragma endregion

#pragma region UI_Button
    // button
    for (int i = 0; i < 12; i++) {
        if (i < progress) {
            tempgui = new GameObject();
            tempgui->GetComponent<Transform>().position = Vector2D_float(((((i * 2 % 12) + 10) * _tileSize) + _midPointX) * RATIO, (((i < 6 ? 7.5f : 5.5f) * _tileSize) + _midPointY) * RATIO);
            tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

            tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
            tempgui->AddComponent<TileSelector>(25, 25);
            tempgui->GetComponent<TileSelector>().SetTile(7, 22);

            tempgui->AddComponent<GUI_Button>("Button");
            tempgui->GetComponent<GUI_Button>().SelectedOffset(4, 22);
        }
        else {
            tempgui = new GameObject();
            tempgui->GetComponent<Transform>().position = Vector2D_float(((((i * 2 % 12) + 10) * _tileSize) + _midPointX) * RATIO, (((i < 6 ? 7.5f : 5.5f) * _tileSize) + _midPointY) * RATIO);
            tempgui->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

            tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_LEVEL_MESH", "LEVEL_SELECT_ASSET_TEX", 1.0f, &camera, false);
            tempgui->AddComponent<TileSelector>(25, 25);
            tempgui->GetComponent<TileSelector>().SetTile(1, 19);

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
        tempgui->AddComponent<TileSelector>(25, 25);
        tempgui->GetComponent<TileSelector>().SetTile((i * 2 % 16) + 1, (i < 8 ? 17 : 15));

        tempgui->AddComponent<GUI_Text>("Number");

        gui_arr.PushGUI(tempgui);
    }

    // Back

    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((3.5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(14, 14);
    tempgui->GetComponent<TileSelector>().SetTile(10, 9);

    tempgui->AddComponent<GUI_Button>("Back");
    tempgui->GetComponent<GUI_Button>().SelectedOffset(12, 9);
    tempgui->GetComponent<GUI_Button>().m_function = GoTo_MenuL;
    gui_arr.PushGUI(tempgui);

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

    if (audioController.Find("BGM")->isPlayed == true)
    {
        audioController.Stop();
        audioController.Find("BGM")->isPlayed = false;
    }

    audioController.Play("Menu");
    audioController.Find("Menu")->isPlayed = true;
}

void LevelSelect::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    //audioController.Stop();
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