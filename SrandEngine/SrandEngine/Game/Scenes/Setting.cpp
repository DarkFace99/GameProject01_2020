#include "Setting.h"

Setting::Setting()
	: Scene("Setting")
{}
Setting::~Setting()
{
	Clean();
}

GameObject* buttonF = nullptr;
GameObject* sliderM = nullptr;
GameObject* sliderS = nullptr;

void GoTo_MenuS() { Engine::get().GoToScene(0); }
void Increase_MU() { 
    SR_TRACE("Slider_MU: +"); 
    AudioController::get().ChangeVolume(1, SoundType::MUSIC);
}
void Decrease_MU() { 
    SR_TRACE("Slider_MU: -");
    AudioController::get().ChangeVolume(0, SoundType::MUSIC);
}
void Increase_SF() {
    SR_TRACE("Slider_SF: +");
    AudioController::get().ChangeVolume(1, SoundType::EFFECT);
}
void Decrease_SF() {
    SR_TRACE("Slider_SF: -");
    AudioController::get().ChangeVolume(0, SoundType::EFFECT);
}

//place_holder
bool full = false;
void ToggleFullScreen() {
    full = !full;
    buttonF->GetComponent<GUI_Button>().SetAttach(full);
    WindowProperties::get().SetFullScreen(full);
}

void NonSaveSettings() 
{
    bool isFullScreen = false;
    float volMusic = 1.0f, volEffect = 1.0f;

    int temp; //IGNORED

    Engine::get().LoadSave(isFullScreen, volMusic, volEffect, temp);

    WindowProperties::get().SetFullScreen(isFullScreen);
    AudioController::get().SetMusicVolume(volMusic);
    AudioController::get().SetMusicVolume(volEffect);
}

void DefaultSetting()
{
    WindowProperties::get().SetFullScreen(false);
    AudioController::get().SetAllVolume(1.0f);
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
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,
        - 1,46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,
        - 1,-1,-1,41,42,42,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,27,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
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

    //sign
    gameObject = new GameObject();
    manager->AddEntity(gameObject);

    gameObject->GetComponent<Transform>().position = Vector2D_float(((26.5 * _tileSize) + _midPointX) * RATIO, ((6.75 * _tileSize) + _midPointY) * RATIO);
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
    // board
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((8.5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(20 * 16 * RATIO, 13 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BOARD_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 11);

    tempgui->AddComponent<GUI_Text>("BOARD");
    gui_arr.PushGUI(tempgui);

    // save
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((7.40 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(3 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_WORD3_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(14, 10);

    tempgui->AddComponent<GUI_Text>("SAVE");
    gui_arr.PushGUI(tempgui);

    //--------------------------------------------

    //Slot1
    tempgui = new GameObject();
    buttonF = tempgui;
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((11.70 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(0, 3);

    tempgui->AddComponent<GUI_Button>("FULLSCREEN");
    tempgui->GetComponent<GUI_Button>().Conceal();
    tempgui->GetComponent<GUI_Button>().m_function = ToggleFullScreen;
    gui_arr.PushGUI(tempgui);

    //pin1 

    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((22.8 * _tileSize) + _midPointX) * RATIO, ((11.75 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_KEY_MESH", "SETTING_ASSET_TEX", (full)? 1.0f : 0.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(7, 6);

    tempgui->AddComponent<GUI_Text>("PIN1");

    buttonF->GetComponent<GUI_Button>().AttachObj(tempgui);

    gui_arr.PushGUI(tempgui);
    

    //Slot2
    tempgui = new GameObject();
    sliderM = tempgui;
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((10.30 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(0, 3);

    tempgui->AddComponent<GUI_Slider>("MUSIC");
    tempgui->GetComponent<GUI_Slider>().Conceal();
    tempgui->GetComponent<GUI_Slider>().m_function = Increase_MU;
    tempgui->GetComponent<GUI_Slider>().n_function = Decrease_MU;
    gui_arr.PushGUI(tempgui);

    //Slot3
    tempgui = new GameObject();
    sliderS = tempgui;
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((8.80 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(19 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(0, 3);

    tempgui->AddComponent<GUI_Slider>("SFX");
    tempgui->GetComponent<GUI_Slider>().Conceal();
    tempgui->GetComponent<GUI_Slider>().m_function = Increase_SF;
    tempgui->GetComponent<GUI_Slider>().n_function = Decrease_SF;
    gui_arr.PushGUI(tempgui);

    //Slot4
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((14.75 * _tileSize) + _midPointX) * RATIO, ((7.40 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(9 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_SLOT_SELECT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(0, 3);

    tempgui->AddComponent<GUI_Button>("CONFIRM");
    tempgui->GetComponent<GUI_Button>().Conceal();
    //stempgui->GetComponent<GUI_Button>().m_function;
    gui_arr.PushGUI(tempgui);
    
    //default

    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((4 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(6 * 16 * RATIO, 3 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_DEFAULT_MESH", "SETTING_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(0, 0);

    tempgui->AddComponent<GUI_Button>("Default");
    tempgui->GetComponent<GUI_Button>().SelectedOffset(6, 0);
    gui_arr.PushGUI(tempgui);

    // Back

    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((15 * _tileSize) + _midPointX) * RATIO, ((1.5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(14, 14);
    tempgui->GetComponent<TileSelector>().SetTile(10, 9);

    tempgui->AddComponent<GUI_Button>("Back");
    tempgui->GetComponent<GUI_Button>().SelectedOffset(12, 9);
    tempgui->GetComponent<GUI_Button>().m_function = GoTo_MenuS;
    gui_arr.PushGUI(tempgui);
#pragma endregion

    if (audioController.Find("BGM")->isPlayed == true)
    {
        audioController.Stop();
        audioController.Find("BGM")->isPlayed = false;
    }

    audioController.Play("Menu");
    audioController.Find("Menu")->isPlayed = true;
}

void Setting::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    //audioController.Stop();
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
