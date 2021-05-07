#include "MainMenu.h"

MainMenu::MainMenu() :Scene("MainMenu")
{}

MainMenu::~MainMenu()
{
	Clean();
}

void StartGame() { Engine::get().GoToScene(3); }
void GoTo_Setting() { Engine::get().GoToScene(1); }
void GoTo_LevelSelect() { Engine::get().GoToScene(2); }
void QuitGame() { Engine::get().Quit(); }

void MainMenu::Init()
{
	manager = &EntityManager::get();
    std::vector<glm::vec4> tile_info;
    GameObject* tempgui = nullptr;
    GameObject* stored = nullptr;

    /* BACKGROUND */
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(0 * RATIO, 0 * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(480 * RATIO, 270 * RATIO);

        gameObject->AddComponent<SpriteRenderer>("BG_MESH", "BG_TEX", 1.0f, &camera, false);
    }

    /* Decor */
    {
        // sign1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((2 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        gameObject->AddComponent<SpriteRenderer>("2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(7, 8);

        // sign2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((28 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);

        gameObject->AddComponent<SpriteRenderer>("2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(7, 8);

        // keys-left
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((5 * _tileSize) + _midPointX) * RATIO, ((2.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(9, 23);

        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((5 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(11, 23);

        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((4 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(13, 23);

        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((6 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(15, 23);

        // keys-right
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((24 * _tileSize) + _midPointX) * RATIO, ((2 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(11, 21);

        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((25 * _tileSize) + _midPointX) * RATIO, ((2 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(13, 21);

        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((26 * _tileSize) + _midPointX) * RATIO, ((2 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>("UI_KEY_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(25, 25);
        gameObject->GetComponent<TileSelector>().SetTile(9, 21);
    }

    



    // TILE SET
#pragma region TileSet

    //1.)create 2D array type int
    //2.)store number from 1 to 16
    //2.)for loop entire map
    //2.)assign tile_info with if statements (Binary Search Method)

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
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,42,42,42,42,43,-1,-1,-1,46,-1,-1,-1,46,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        - 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10

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

#pragma region CharacterAssets 

    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(((8 * _tileSize) + _midPointX) * RATIO, ((2.5 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<RigidBody>(2.0f);
    // anim_set
    gameObject->AddComponent<Animator>(18, 80);
    gameObject->GetComponent<Animator>().SetState("BENNY_OUT", 0, 0);
    gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 1, 6);
    gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 7, 15);
    gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 16, 16);
    gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 17, 17);
    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y - 5,
        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

    gameObject->AddComponent<Benny>(); // test CC mechanics
   // gameObject->GetComponent<Benny>().SetActive(false);

    //player = gameObject; // check collision
    //benny = player;
    levelManager.AddObject(gameObject);
    objManager.PushObject(gameObject);

    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(((28.5 * _tileSize) + _midPointX) * RATIO, ((5 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "CHERRY_ANIM_MESH", "CHERRY_ANIM_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<RigidBody>(2.0f);
    // anim_set
    gameObject->AddComponent<Animator>(25, 80);
    gameObject->GetComponent<Animator>().SetState("CHERRY_OUT", 0, 0);
    gameObject->GetComponent<Animator>().SetState("CHERRY_IDLE", 1, 6);
    gameObject->GetComponent<Animator>().SetState("CHERRY_RUN", 7, 15);
    gameObject->GetComponent<Animator>().SetState("CHERRY_JUMP", 16, 16);
    gameObject->GetComponent<Animator>().SetState("CHERRY_FALL", 17, 17);
    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y - 5,
        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

    gameObject->AddComponent<Cherry>(); // test CC mechanics
    //gameObject->GetComponent<Cherry>().SetActive(false);

    objManager.PushObject(gameObject);
    levelManager.AddObject(gameObject);

    //UI_Box
    gameObject = new GameObject();
    stored = gameObject;
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(((7 * _tileSize) + _midPointX) * RATIO, ((6 * _tileSize) + _midPointY) * RATIO);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(5 * 16 * RATIO, 5 * 16 * RATIO);
    gameObject->AddComponent<SpriteRenderer>("B_MESH", "B_TEX", 0.0f, &camera, false);
    
    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y ,
        true /* overlap */, false /* movable *//*, "BENNY_ANIM_MESH", &camera*/);
    gameObject->AddComponent<UI_Box>();
    gameObject->GetComponent<UI_Box>().Attach(&gui_arr);

    objManager.PushObject(gameObject);
    levelManager.AddObject(gameObject);

    levelManager.SetUpCC();
#pragma endregion

#pragma region UI_Button

    // button1
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((14 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7*16 * RATIO, 2*16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 19);

    tempgui->AddComponent<GUI_Button>("PlayButton");
    tempgui->GetComponent<GUI_Button>().m_function = StartGame;
    tempgui->GetComponent<GUI_Button>().SelectedOffset(1, 22);
    
    gui_arr.PushGUI(tempgui);

    // button2
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((11 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 19);
    
    tempgui->AddComponent<GUI_Button>("SettingButton");
    tempgui->GetComponent<GUI_Button>().m_function = GoTo_Setting;
    tempgui->GetComponent<GUI_Button>().SelectedOffset(1, 22);

    gui_arr.PushGUI(tempgui);

    // button3
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((8 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 19);

    tempgui->AddComponent<GUI_Button>("LevelButton");
    tempgui->GetComponent<GUI_Button>().m_function = GoTo_LevelSelect;
    tempgui->GetComponent<GUI_Button>().SelectedOffset(1, 22);

    gui_arr.PushGUI(tempgui);

    // button4
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(7 * 16 * RATIO, 2 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_BUTTON_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 19);

    tempgui->AddComponent<GUI_Button>("ExitButton");
    tempgui->GetComponent<GUI_Button>().m_function = QuitGame;
    tempgui->GetComponent<GUI_Button>().SelectedOffset(1, 22);

    gui_arr.PushGUI(tempgui);

    //Text

    // text1
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((14 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(6 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_WORD6_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(0, 17);

    tempgui->AddComponent<GUI_Text>("Play");

    gui_arr.PushGUI(tempgui);

    // text2
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((11 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(6 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_WORD6_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 15);

    tempgui->AddComponent<GUI_Text>("Setting");

    gui_arr.PushGUI(tempgui);

    // text3
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((8 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(5 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_WORD5_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 13);

    tempgui->AddComponent<GUI_Text>("Levels");

    gui_arr.PushGUI(tempgui);

    // text4
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, ((5 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(3 * 16 * RATIO, 1 * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_WORD3_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(25, 25);
    tempgui->GetComponent<TileSelector>().SetTile(1, 11);

    tempgui->AddComponent<GUI_Text>("Exit");

    gui_arr.PushGUI(tempgui);

    for (int i = 0; i < 4; i++) {
        tempgui = new GameObject();
        tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, (((13.95 - (i * 3)) * _tileSize) + _midPointY) * RATIO);
        tempgui->GetComponent<Transform>().scale = Vector2D_float(8 * 16 * RATIO, 3 * 16 * RATIO);

        tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "UI_OUTLINE_MESH", "MENU_ASSET_TEX", 1.0f, &camera, false);
        tempgui->AddComponent<TileSelector>(25, 25);
        tempgui->GetComponent<TileSelector>().SetTile(13, 13);
        
        gui_arr.PushGUI(tempgui);
        stored->GetComponent<UI_Box>().Add(tempgui);
        stored->GetComponent<UI_Box>().SetRender(false);
    }

#pragma endregion

    // selector

    tempgui = new GameObject();
    //tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, (((13.95 - (i * 3)) * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(8 * RATIO, 8 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "B_MESH", "B_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<Animator>(3, 100);
    tempgui->GetComponent<Animator>().SetState("WHITE", 0, 0);
    tempgui->GetComponent<Animator>().SetState("YELLOW", 1, 1);
    tempgui->GetComponent<Animator>().SetState("RED", 2, 2);

    tempgui->AddComponent<GUI_Selector>();
    levelManager.SetSelector(&tempgui->GetComponent<GUI_Selector>());
    gui_arr.SetSelector(&tempgui->GetComponent<GUI_Selector>());
    gui_arr.PushGUI(tempgui);
    

    // title
    tempgui = new GameObject();
    tempgui->GetComponent<Transform>().position = Vector2D_float(((20 * _tileSize) + _midPointX) * RATIO, ((11 * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(20/1.2f * 16 * RATIO, 7/1.2f * 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "TITLE_MESH", "TITLE_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<TileSelector>(20, 16);
    tempgui->GetComponent<TileSelector>().SetTile(0, 7);

    tempgui->AddComponent<GUI_Text>("Title");

    gui_arr.PushGUI(tempgui);
    gui_arr.SetControl(false);

    if (audioController.Find("BGM")->isPlayed == true) 
    {
        audioController.Stop();
        audioController.Find("BGM")->isPlayed = false;
    }
    
    audioController.Play("Menu");
    audioController.Find("Menu")->isPlayed = true;
}

void MainMenu::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    //audioController.Stop();
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
    levelManager.AbilityControl();
    gui_arr.OnUpdate();
}