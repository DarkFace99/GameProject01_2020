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
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 2);

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
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 2);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(4, 1);

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

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 6);


    }

    // DOOR
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (8 * 16)) * RATIO, (_midPointY + _offset + (7.5 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 64.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 8);

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
        gameObject->AddComponent<Animator>(21, 100);
        gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 6);
        gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 8, 16);
        gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 18, 18);
        gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 19, 19);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Benny>(); // test CC mechanics

        //player = gameObject; // check collision
        //benny = player;

        objManager.PushObject(gameObject);
        levelManager.AddObject(gameObject);
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
       /* gameObject->AddComponent<Animator>(1, 100);
        gameObject->GetComponent<Animator>().SetState("BARTER_IDLE", 0, 0);*/
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Barter>();

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
        gameObject->AddComponent<Animator>(20, 100);
        gameObject->GetComponent<Animator>().SetState("MACHO_IDLE", 0, 4);
        gameObject->GetComponent<Animator>().SetState("MACHO_RUN", 13, 19);
        gameObject->GetComponent<Animator>().SetState("IDLE", 0, 4);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Macho>(); // test CC mechanics

        objManager.PushObject(gameObject);
        levelManager.AddObject(gameObject);

    }

    levelManager.SetUpCC();

#pragma endregion

    //audioController.Play("BGM");
}

void Level3::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    audioController.Stop();
}

void Level3::Draw()
{
    manager->Draw();
}

void Level3::Update()
{
    manager->Update();
    levelManager.AbilityControl();
}
