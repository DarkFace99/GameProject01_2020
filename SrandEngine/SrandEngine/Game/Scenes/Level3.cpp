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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (11 * 16)) * RATIO, (-135.0f + 88) * RATIO);
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (20 * 16)) * RATIO, (-135.0f + 88) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(4, 2);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(4, 1);

        button2 = gameObject;
        objManager.PushObject(gameObject);

        // 3
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (19 * 16)) * RATIO, (-135.0f + 164) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(4, 2);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            true, false/*, "BUTTON_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -8);
        gameObject->AddComponent<Button>(4, 1);

        button3 = gameObject;
        objManager.PushObject(gameObject);
    }

    // DOOR_STAND
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (14 * 16)) * RATIO, (-135.0f + 164) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 6);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (18 * 16)) * RATIO, (-135.0f + 72) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);
        gameObject->GetComponent<Transform>().rotationAngle = 90;

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(3, 6);
    }

    // DOOR
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (14 * 16)) * RATIO, (-135.0f + 196 + 8) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 64.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 8);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
            false, false/*, "DOOR_MESH", &camera*/);
        gameObject->AddComponent<Door>();
        gameObject->GetComponent<Door>().AddConnectedButtons(button1);

        objManager.PushObject(gameObject);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (16 * 16)) * RATIO, (-135.0f + 64 + 8) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(64.0f * RATIO, 16.0f * RATIO);
        gameObject->GetComponent<Transform>().rotationAngle = 90;

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(3, 8);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
            false, false/*, "DOOR_MESH", &camera*/);
        gameObject->AddComponent<Door>(false);
        gameObject->GetComponent<Door>().AddConnectedButtons(button2);
        gameObject->GetComponent<Door>().AddConnectedButtons(button3);

        objManager.PushObject(gameObject);
    }

    // ELEVATOR
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (7 * 16)) * RATIO, (-135.0f + 16) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 32.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 4);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
            false, false/*, "ELEVATOR_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -2.0f * RATIO);
        gameObject->AddComponent<Elevator>(4 * 16 * RATIO);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button1);

        objManager.PushObject(gameObject);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (25 * 16)) * RATIO, (-135.0f + 80) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 32.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(4, 4);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
            false, false/*, "ELEVATOR_MESH", &camera*/);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(0.0f, -2.0f * RATIO);
        gameObject->AddComponent<Elevator>(5 * 16 * RATIO);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button2);
        gameObject->GetComponent<Elevator>().AddConnectedButtons(button3);

        objManager.PushObject(gameObject);
    }

    // ELEVATOR_STAND
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (7 * 16)) * RATIO, (-135.0f + 8) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(1, 3);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (25 * 16)) * RATIO, (-135.0f + 72) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "ELEVATOR_STAND_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(10, 13);
        gameObject->GetComponent<TileSelector>().SetTile(4, 3);
    }

#pragma endregion

#pragma region CharacterAssets 

    ///* Character */

    //// NPC
    //{
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);
    //    gameObject->GetComponent<Transform>().position = Vector2D_float(-122.0f, 130.0f);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "NPC_ANIM_MESH", "NPC_ANIM_TEX", 1.0f, &camera, false);
    //    // anim_set
    //    gameObject->AddComponent<Animator>(2, 100);
    //    gameObject->GetComponent<Animator>().SetState("NPC_SAD", 0, 0);
    //    gameObject->GetComponent<Animator>().SetState("NPC_HAPPY", 1, 1);
    //    gameObject->GetComponent<Animator>().PlayState("NPC_SAD");

    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
    //        true /* overlap */, false /* movable *//*, "BENNY_ANIM_MESH", &camera*/);
    //    gameObject->AddComponent<NPC>();

    //    /*npc = gameObject;*/
    //    objManager.PushObject(gameObject);
    //}

    //// Benny
    //{
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);
    //    gameObject->GetComponent<Transform>().position = Vector2D_float(-555.0f, -200.0f);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<RigidBody>(2.0f);
    //    // anim_set
    //    gameObject->AddComponent<Animator>(21, 100);
    //    gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 6);
    //    gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 8, 16);
    //    gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 18, 18);
    //    gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 19, 19);
    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
    //        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

    //    gameObject->AddComponent<Benny>(); // test CC mechanics

    //    //player = gameObject; // check collision
    //    //benny = player;

    //    objManager.PushObject(gameObject);
    //    levelManager.AddObject(gameObject);
    //}

    ////// Macho
    ////{
    ////    gameObject = new GameObject();
    ////    manager->AddEntity(gameObject);
    ////    gameObject->GetComponent<Transform>().position = Vector2D_float(60.0f, -285.0f);
    ////    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    ////    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "MACHO_ANIM_MESH", "MACHO_ANIM_TEX", 1.0f, &camera, true);
    ////    gameObject->AddComponent<RigidBody>(2.0f);

    ////    gameObject->AddComponent<Animator>(20, 100);
    ////    gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 4);
    ////    gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 13, 19);
    ////    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
    ////        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);
    ////    
    ////    //gameObject->AddComponent<Macho>(); // test CC mechanics

    ////    /*macho = gameObject;*/
    ////    objManager.PushObject(gameObject);
    ////    levelManager.AddObject(gameObject);
    ////}

    //// Cherry
    //{
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);
    //    gameObject->GetComponent<Transform>().position = Vector2D_float(-235.0f, -200.0f);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "CHERRY_ANIM_MESH", "CHERRY_ANIM_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<RigidBody>(2.0f);
    //    // anim_set
    //    gameObject->AddComponent<Animator>(19, 100);
    //    gameObject->GetComponent<Animator>().SetState("CHERRY_IDLE", 1, 6);
    //    gameObject->GetComponent<Animator>().SetState("CHERRY_RUN", 7, 15);
    //    gameObject->GetComponent<Animator>().SetState("CHERRY_JUMP", 16, 16);
    //    gameObject->GetComponent<Animator>().SetState("CHERRY_FALL", 17, 17);
    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
    //        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

    //    gameObject->AddComponent<Cherry>(); // test CC mechanics

    //    objManager.PushObject(gameObject);
    //    levelManager.AddObject(gameObject);
    //}

    //// Pear
    //{
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);
    //    gameObject->GetComponent<Transform>().position = Vector2D_float(100.0f, -200.0f);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "PEAR_ANIM_MESH", "PEAR_ANIM_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<RigidBody>(2.0f);
    //    // anim_set
    //    gameObject->AddComponent<Animator>(19, 100);
    //    gameObject->GetComponent<Animator>().SetState("PEAR_IDLE", 1, 6);
    //    gameObject->GetComponent<Animator>().SetState("PEAR_RUN", 7, 16);
    //    gameObject->GetComponent<Animator>().SetState("PEAR_JUMP", 17, 17);
    //    gameObject->GetComponent<Animator>().SetState("PEAR_FALL", 18, 18);
    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
    //        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

    //    gameObject->AddComponent<Pear>();

    //    objManager.PushObject(gameObject);
    //    levelManager.AddObject(gameObject);
    //}

    //// Barter
    //{
    //    gameObject = new GameObject();
    //    manager->AddEntity(gameObject);
    //    gameObject->GetComponent<Transform>().position = Vector2D_float(300.0f, 300.0f);
    //    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    //    gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BARTER_ANIM_MESH", "BARTER_ANIM_TEX", 1.0f, &camera, false);
    //    gameObject->AddComponent<RigidBody>(2.0f);
    //    // anim_set
    //   /* gameObject->AddComponent<Animator>(1, 100);
    //    gameObject->GetComponent<Animator>().SetState("BARTER_IDLE", 0, 0);*/
    //    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
    //        false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

    //    gameObject->AddComponent<Barter>();

    //    objManager.PushObject(gameObject);
    //    levelManager.AddObject(gameObject);
    //}


    //levelManager.SetUpCC();

#pragma endregion

    audioController.Play("BGM");

}

void Level3::Clean()
{
    manager->Clean();
    objManager.Clean();
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
