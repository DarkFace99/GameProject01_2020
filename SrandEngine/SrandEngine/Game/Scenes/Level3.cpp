#include "Level3.h"

Level3::Level3()
	:Scene("Level3")
{}

Level3::~Level3()
{
	Clean();
}

void Level3::Init()
{
    manager = &EntityManager::get();

    std::vector<glm::vec4> tile_info;

#pragma region LevelAssets

    /* BACKGROUND */
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float(0 * RATIO, 0 * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(480 * RATIO, 270 * RATIO);

        gameObject->AddComponent<SpriteRenderer>("BG_MESH", "BG_TEX", 1.0f, &camera, false);
    }

    /* Tile Set */
    {
        /* First Row */
        for (int i = 0; i < 30; i++)
        {
            tile_info.push_back(glm::vec4(i, 0, 2, 2));
        }
        /* Sixth Row */
        for (int i = 0; i < 30; i++)
        {
            if (i == 0) { tile_info.push_back(glm::vec4(i, 5, 1, 2)); }
            else if (i == 29) { tile_info.push_back(glm::vec4(i, 5, 3, 2)); }
            else { tile_info.push_back(glm::vec4(i, 5, 2, 2)); }

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

    /* Level Asset */

    // BUTTON
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (3 * 16)) * RATIO, (_midPointY + _offset + (6 * _tileSize)) * RATIO);
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (20 * 16)) * RATIO, (_midPointY + _offset + (1 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 3);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(1, 1);

        button2 = gameObject;
        objManager.PushObject(gameObject);

    }

    // DOOR_STAND
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (8 * 16)) * RATIO, (_midPointY + _offset + (5 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 7);


    }

    // DOOR
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (8 * 16)) * RATIO, (_midPointY + _offset + (7.5 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 64.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 9);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
            false, false/*, "DOOR_MESH", &camera*/);
        gameObject->AddComponent<Door>();
        gameObject->GetComponent<Door>().AddConnectedButtons(button1);
        gameObject->GetComponent<Door>().AddConnectedButtons(button2);

        objManager.PushObject(gameObject);
    }

#pragma endregion

#pragma region CharacterAssets 

    // Benny
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(-555.0f, -270.0f);
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
        levelManager.AddObject(gameObject);
        objManager.PushObject(gameObject);
    }

    // Barter
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(-360.0f, -60.0f);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BARTER_ANIM_MESH", "BARTER_ANIM_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<RigidBody>(2.0f);
        // anim_set
        gameObject->AddComponent<Animator>(11, 80);
        gameObject->GetComponent<Animator>().SetState("BARTER_OUT", 0, 0);
        gameObject->GetComponent<Animator>().SetState("BARTER_IDLE", 1, 9);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Barter>(); // test CC mechanics
        objManager.PushObject(gameObject);
        levelManager.AddObject(gameObject);
    }

    // Macho (last due to the Carry())
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(200.0f, -60.0f);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "MACHO_ANIM_MESH", "MACHO_ANIM_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<RigidBody>(2.0f);
        // anim_set
        gameObject->AddComponent<Animator>(21, 80);
        gameObject->GetComponent<Animator>().SetState("MACHO_OUT", 0, 0);
        gameObject->GetComponent<Animator>().SetState("MACHO_IDLE", 1, 12);
        gameObject->GetComponent<Animator>().SetState("MACHO_RUN", 13, 19);
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
        gameObject->GetComponent<Transform>().position = Vector2D_float(650.0f, -100.0f);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(1.0f, 800.0f);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 0.0f, &camera, false);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::GOAL_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
            true /* overlap */, false /* movable */, "BENNY_ANIM_MESH" /* any mesh is fine as long as 1:1 */, &camera);

        objManager.PushObject(gameObject);
        levelManager.SetGoal(*gameObject);
    }

    levelManager.SetUpCC();

#pragma endregion

    if (audioController.Find("Menu")->isPlayed == true)
    {
        audioController.Stop();
        audioController.Find("Menu")->isPlayed = false;
    }

    audioController.Play("BGM");
    audioController.Find("BGM")->isPlayed = true;

    //progress = 3;
}

void Level3::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    //audioController.Stop();
}

void Level3::Draw()
{
    manager->Draw();
}

void Level3::Update()
{
    manager->Update();
    levelManager.CheckGoal();
    levelManager.AbilityControl();
}
