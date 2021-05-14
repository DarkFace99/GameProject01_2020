#include "Lv3.h"

Lv3::Lv3()
    : Scene("Lv3")
{}

Lv3::~Lv3()
{
    Clean();
}

void Lv3::Init()
{
    manager = &EntityManager::get();
    std::vector<glm::vec4> tile_info;
    GameObject* tempgui = nullptr;

#pragma region LevelAssets

    /* BACKGROUND */
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(0 * RATIO, 0 * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(480 * RATIO, 270 * RATIO);

        gameObject->AddComponent<SpriteRenderer>("BG_MESH", "BG_TEX", 1.0f, &camera, false);
    }


    // TILE SET
#pragma region TileSet

    //1.)create 2D array type int
    //2.)store number from 1 to 16
    //2.)for loop entire map
    //2.)assign tile_info with if statements (Binary Search Method)

    int tileMAP[16][30] = {
        11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        18,-1,-1,-1,-1,-1,41,42,42,42,42,42,42,42,43,43,-1,-1,41,42,42,42,42,42,42,42,42,10,10,10,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,
        19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,
        26,42,42,42,42,42,43,-1,-1,-1,-1, 9,10,10,10,11,-1,-1,-1,-1,-1,-1,-1, 9,10,10,10,18,18,18,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,18,19,-1,-1,-1,-1,-1,-1,-1,17,18,18,18,18,18,18,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,26,26,26,26,27,-1,-1,-1,-1,-1,-1,-1,17,18,18,18,18,18,18,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,18,18,18,18,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,18,18,18,18,18,18,
        10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,18,18,18,18,18,18,18,
    };

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 30; x++)
        {
            switch (tileMAP[y][x])
            {
            default: //printf("empty");
                break;
            case 9: tile_info.push_back(glm::vec4(x, 15 - y, 1, 6)); //1
                break;
            case 10: tile_info.push_back(glm::vec4(x, 15 - y, 2, 6));//2
                break;
            case 11: tile_info.push_back(glm::vec4(x, 15 - y, 3, 6));//3
                break;
            case 17: tile_info.push_back(glm::vec4(x, 15 - y, 1, 5));//4
                break;
            case 18: tile_info.push_back(glm::vec4(x, 15 - y, 2, 5));//5
                break;
            case 19: tile_info.push_back(glm::vec4(x, 15 - y, 3, 5));//6
                break;
            case 25: tile_info.push_back(glm::vec4(x, 15 - y, 1, 4));//7
                break;
            case 26: tile_info.push_back(glm::vec4(x, 15 - y, 2, 4));//8
                break;
            case 27: tile_info.push_back(glm::vec4(x, 15 - y, 3, 4));//9
                break;
            case 14: tile_info.push_back(glm::vec4(x, 15 - y, 6, 6));//10
                break;
            case 22: tile_info.push_back(glm::vec4(x, 15 - y, 6, 5));//11
                break;
            case 30: tile_info.push_back(glm::vec4(x, 15 - y, 6, 4));//12
                break;
            case 41: tile_info.push_back(glm::vec4(x, 15 - y, 1, 2));//13
                break;
            case 42: tile_info.push_back(glm::vec4(x, 15 - y, 2, 2));//14
                break;
            case 43: tile_info.push_back(glm::vec4(x, 15 - y, 3, 2));//15
                break;
            case 46: tile_info.push_back(glm::vec4(x, 15 - y, 6, 2));//16
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

    /* Level Asset */

    // BUTTON
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((2.5 * _tileSize) + _midPointX) * RATIO, ((6.5 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 3);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(1, 1);

        button1 = gameObject;
        objManager.PushObject(gameObject);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((14 * _tileSize) + _midPointX) * RATIO, ((6.5 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(4, 3);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(4, 1);

        button2 = gameObject;
        objManager.PushObject(gameObject);

        // 3
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((14 * _tileSize) + _midPointX) * RATIO, ((11.5 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 3);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(1, 1);

        button3 = gameObject;
        objManager.PushObject(gameObject);
    }

    //// DOOR_STAND
    //{
    //    // 1
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);

    //    gameObject->GetComponent<Transform>().position = Vector2D_float(((23.5 * _tileSize) + _midPointX) * RATIO, ((4.5 * _tileSize) + _midPointY) * RATIO);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);
    //    gameObject->GetComponent<Transform>().rotationAngle = 90;

    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<TileSelector>(14, 14);
    //    gameObject->GetComponent<TileSelector>().SetTile(3, 7);

    //}

    //// DOOR
    //{
    //    // 1
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);

    //    gameObject->GetComponent<Transform>().position = Vector2D_float(((21 * _tileSize) + _midPointX) * RATIO, ((4.5 * _tileSize) + _midPointY) * RATIO);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(64.0f * RATIO, 16.0f * RATIO);
    //    gameObject->GetComponent<Transform>().rotationAngle = 90;

    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<TileSelector>(14, 14);
    //    gameObject->GetComponent<TileSelector>().SetTile(3, 9);

    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::DOOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
    //        false, false/*, "DOOR_MESH", &camera*/);
    //    gameObject->AddComponent<Door>();
    //    gameObject->AddComponent<Door>(false);
    //    gameObject->GetComponent<Door>().AddConnectedButtons(button2);

    //    objManager.PushObject(gameObject);

    //    // 1 extended
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);

    //    gameObject->GetComponent<Transform>().position = Vector2D_float(((18 * _tileSize) + _midPointX) * RATIO, ((4.5 * _tileSize) + _midPointY) * RATIO);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(64.0f * RATIO, 16.0f * RATIO);
    //    gameObject->GetComponent<Transform>().rotationAngle = 90;

    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<TileSelector>(14, 14);
    //    gameObject->GetComponent<TileSelector>().SetTile(3, 9);

    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::DOOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
    //        false, false/*, "DOOR_MESH", &camera*/);
    //    gameObject->AddComponent<Door>();
    //    gameObject->AddComponent<Door>(false);
    //    gameObject->GetComponent<Door>().AddConnectedButtons(button2);

    //    objManager.PushObject(gameObject);
    //}

    // ELEVATOR
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((8 * _tileSize) + _midPointX) * RATIO, ((1 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 32.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 5);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ELEVATOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
            false, false/*, "ELEVATOR_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -2.0f * RATIO);
        gameObject->AddComponent<Elevator>(5 * 16 * RATIO);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button1);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button3);

        objManager.PushObject(gameObject);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((5 * _tileSize) + _midPointX) * RATIO, ((6 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 32.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(4, 5);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ELEVATOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
            false, false/*, "ELEVATOR_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -2.0f * RATIO);
        gameObject->AddComponent<Elevator>(5 * 16 * RATIO);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button2);

        objManager.PushObject(gameObject);

        // 3
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((17 * _tileSize) + _midPointX) * RATIO, ((6 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 32.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 5);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ELEVATOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
            false, false/*, "ELEVATOR_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -2.0f * RATIO);
        gameObject->AddComponent<Elevator>(5 * 16 * RATIO);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button1);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button3);
        gameObject->GetComponent<Elevator>().SetInverse();

        objManager.PushObject(gameObject);

    }

    // ELEVATOR_STAND
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((8 * _tileSize) + _midPointX) * RATIO, ((0.5 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 4);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(((5 * _tileSize) + _midPointX) * RATIO, ((5.5 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(4, 4);
    }

#pragma endregion

#pragma region CharacterAssets 

    /* Character */

    // NPC
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((25 * _tileSize) + _midPointX) * RATIO, ((6.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "NPC_ANIM_MESH", "NPC_ANIM_TEX", 1.0f, &camera, false);
        // anim_set
        gameObject->AddComponent<Animator>(2, 100);
        gameObject->GetComponent<Animator>().SetState("NPC_SAD", 0, 0);
        gameObject->GetComponent<Animator>().SetState("NPC_HAPPY", 1, 1);
        gameObject->GetComponent<Animator>().PlayState("NPC_SAD");

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            true /* overlap */, false /* movable *//*, "BENNY_ANIM_MESH", &camera*/);
        gameObject->AddComponent<NPC>();

        objManager.PushObject(gameObject);
    }

    // Benny
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((3 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<RigidBody>(2.0f);
        // anim_set
        gameObject->AddComponent<Animator>(18, 80);
        gameObject->GetComponent<Animator>().SetState("BENNY_IN", 0, 0);
        gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 1, 6);
        gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 7, 15);
        gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 16, 16);
        gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 17, 17);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y - 5,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Benny>(); // test CC mechanics
        levelManager.AddObject(gameObject);
        objManager.PushObject(gameObject);
    }

    // Macho (last due to the Carry())
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((13 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "MACHO_ANIM_MESH", "MACHO_ANIM_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<RigidBody>(2.0f);
        // anim_set
        gameObject->AddComponent<Animator>(21, 80);
        gameObject->GetComponent<Animator>().SetState("MACHO_IN", 0, 0);
        gameObject->GetComponent<Animator>().SetState("MACHO_IDLE", 1, 12);
        gameObject->GetComponent<Animator>().SetState("MACHO_RUN", 13, 18);
        gameObject->GetComponent<Animator>().SetState("MACHO_FALL", 19, 19);
        gameObject->GetComponent<Animator>().SetState("MACHO_OUT", 20, 20);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Macho>(); // test CC mechanics
        objManager.PushObject(gameObject);
        levelManager.AddObject(gameObject);

    }

    // Goal
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((29 * _tileSize) + _midPointX) * RATIO, ((12 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 0.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(11, 2);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::GOAL_COLLISION, gameObject->GetComponent<Transform>().scale.x / 4, gameObject->GetComponent<Transform>().scale.y * 2,
            true /* overlap */, false /* movable */, "BENNY_ANIM_MESH" /* any mesh is fine as long as 1:1 */, &camera);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(1.5 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<Goal>(11, 4);

        objManager.PushObject(gameObject);
        levelManager.SetGoal(*gameObject);
    }

    levelManager.SetUpCC();

#pragma endregion

#pragma region GUI

    // selector

    tempgui = new GameObject();
    //tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, (((13.95 - (i * 3)) * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(8 * RATIO, 8 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "SELECTOR_MESH", "SELECTOR_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<Animator>(3, 100);
    tempgui->GetComponent<Animator>().SetState("WHITE", 0, 0);
    tempgui->GetComponent<Animator>().SetState("YELLOW", 1, 1);
    tempgui->GetComponent<Animator>().SetState("RED", 2, 2);

    tempgui->AddComponent<GUI_Selector>();
    levelManager.SetSelector(&tempgui->GetComponent<GUI_Selector>());
    gui_arr.SetSelector(&tempgui->GetComponent<GUI_Selector>());
    gui_arr.PushGUI(tempgui);

    gui_arr.SetControl(false);
#pragma endregion

    Engine::get().PlayBGM();
}
void Lv3::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    gui_arr.Clear();
}
void Lv3::Draw()
{
    manager->Draw();
    gui_arr.OnDraw();
}
void Lv3::Update()
{
    manager->Update();
    levelManager.CheckGoal();
    levelManager.AbilityControl();
    gui_arr.OnUpdate();
}
