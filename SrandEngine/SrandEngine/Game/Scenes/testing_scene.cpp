#include "testing_scene.h"

//#include "Source/Camera.h"
//
//#include "Entity/Button.h"
//#include "Entity/Door.h"
//#include "Entity/Elevator.h"
//#include "Entity/NPC.h"
//#include "Entity/Benny.h"
//#include "Entity/Macho.h"
//#include "Entity/Cherry.h"
//#include "Entity/Pear.h"
//#include "Entity/Barter.h"
//
//#include "Source/Audio.h"
//Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);
//ObjManager& objManager = ObjManager::get();
//LevelManager& levelManager = LevelManager::get();
//GameObject* gameObject;
//
//AudioController& audioController = AudioController::get();
//GameObject* npc;
//GameObject* player;
//GameObject* benny;
//GameObject* macho;
//GameObject* button1;
//GameObject* button2;
//GameObject* button3;

TestingScene::TestingScene()
	: Scene("TestingScene")
{}

TestingScene::~TestingScene()
{
    Clean();
}

void TestingScene::Init()
{
    manager = &EntityManager::get();
    GameObject* tempgui = nullptr;
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
            if (i > 5 && i < 29) {  tile_info.push_back(glm::vec4(i, 0, 2, 6)); }
            else {                  tile_info.push_back(glm::vec4(i, 0, 2, 5)); }

        }
        /* Second Row */
        for (int i = 0; i < 7; i++)
        {
            if (i > 5) {            tile_info.push_back(glm::vec4(29, 1, 1, 5)); }
            else if (i == 5) {      tile_info.push_back(glm::vec4(i, 1, 3, 5)); }
            else {                  tile_info.push_back(glm::vec4(i, 1, 2, 5)); }
        }
        /* Third Row */
        for (int i = 0; i < 7; i++)
        {
            if (i > 5) {            tile_info.push_back(glm::vec4(29, 2, 1, 5)); }
            else if (i == 5) {      tile_info.push_back(glm::vec4(i, 2, 3, 6)); }
            else {                  tile_info.push_back(glm::vec4(i, 2, 2, 6)); }
        }
        /* Forth Row */
                                    tile_info.push_back(glm::vec4(29, 3, 1, 5));
        /* Fifth Row */
        for (int i = 8; i < 14; i++)
        {
            if (i == 8) {           tile_info.push_back(glm::vec4(i, 4, 1, 2)); }
            else {                  tile_info.push_back(glm::vec4(i, 4, 2, 2)); }
        }
        for (int i = 18; i < 30; i++)
        {
            if (i == 29) {          tile_info.push_back(glm::vec4(i, 4, 2, 6)); }
            else {                  tile_info.push_back(glm::vec4(i, 4, 2, 2)); }
        }
        /* Tenth Row */
        for (int i = 15; i < 24; i++)
        {
            if (i == 23) {          tile_info.push_back(glm::vec4(i, 9, 3, 2)); }
            else if (i == 15) {     tile_info.push_back(glm::vec4(i, 9, 1, 4)); }
            else if (i == 16) {     tile_info.push_back(glm::vec4(i, 9, 2, 4)); }
            else {                  tile_info.push_back(glm::vec4(i, 9, 2, 2)); }
        }
        /* Eleventh Row */
        for (int i = 9; i < 17; i++)
        {
            if (i == 9) {           tile_info.push_back(glm::vec4(i, 10, 1, 4)); }
            else if (i == 15) {     tile_info.push_back(glm::vec4(i, 10, 2, 6)); }
            else if (i == 16) {     tile_info.push_back(glm::vec4(i, 10, 3, 6)); }
            else {                  tile_info.push_back(glm::vec4(i, 10, 2, 2)); }
        }
        /* Remaining Row */
        for (int i = 1; i < 6; i++)
        {
            if (i < 5) {            tile_info.push_back(glm::vec4(9, 10 + i, 6, 5)); }
            else {                  tile_info.push_back(glm::vec4(9, 10 + i, 6, 6)); }
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (11 * 16)) * RATIO, (_midPointY + _offset + (5 * _tileSize)) * RATIO);
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (20 * 16)) * RATIO, (-135.0f + 88) * RATIO);
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (19 * 16)) * RATIO, (_midPointY + _offset + (10 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "BUTTON_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(4, 3);

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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (14 * 16)) * RATIO, (_midPointY + _offset + (10 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 7);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (18 * 16)) * RATIO, (-135.0f + 72) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);
        gameObject->GetComponent<Transform>().rotationAngle = 90;

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "1x1_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(3, 7);
    }

    // DOOR
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (14 * 16)) * RATIO, (_midPointY + _offset + (12.5 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 64.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 9);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::DOOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
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
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(3, 9);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::DOOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
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

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 5);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ELEVATOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
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

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(4, 5);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ELEVATOR_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 8.0f,
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
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 4);

        // 2
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (25 * 16)) * RATIO, (-135.0f + 72) * RATIO);
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
        gameObject->GetComponent<Transform>().position = Vector2D_float(-122.0f, 136.0f);
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

        /*npc = gameObject;*/
        objManager.PushObject(gameObject);
    }

    // Benny
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((3 * _tileSize) + _midPointX) * RATIO, ((3.75 * _tileSize) + _midPointY) * RATIO);
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

    

    // Cherry
    {
        // Cherry
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((24 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
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
    }
    // Pear
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((16 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "PEAR_ANIM_MESH", "PEAR_ANIM_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<RigidBody>(2.0f);
        // anim_set
        gameObject->AddComponent<Animator>(20, 80);
        gameObject->GetComponent<Animator>().SetState("PEAR_OUT", 0, 0);
        gameObject->GetComponent<Animator>().SetState("PEAR_IDLE", 1, 6);
        gameObject->GetComponent<Animator>().SetState("PEAR_RUN", 7, 16);
        gameObject->GetComponent<Animator>().SetState("PEAR_JUMP", 17, 17);
        gameObject->GetComponent<Animator>().SetState("PEAR_FALL", 18, 18);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Pear>(); // test CC mechanics
        objManager.PushObject(gameObject);
        levelManager.AddObject(gameObject);

    }

    // Barter
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((22 * _tileSize) + _midPointX) * RATIO, ((10.75 * _tileSize) + _midPointY) * RATIO);
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
        gameObject->GetComponent<Transform>().position = Vector2D_float(((13 * _tileSize) + _midPointX) * RATIO, ((1.75 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "MACHO_ANIM_MESH", "MACHO_ANIM_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<RigidBody>(2.0f);
        // anim_set
        gameObject->AddComponent<Animator>(21, 80);
        gameObject->GetComponent<Animator>().SetState("MACHO_OUT", 0, 0);
        gameObject->GetComponent<Animator>().SetState("MACHO_IDLE", 1, 12);
        gameObject->GetComponent<Animator>().SetState("MACHO_RUN", 13, 18);
        gameObject->GetComponent<Animator>().SetState("MACHO_FALL", 19, 19);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
            false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

        gameObject->AddComponent<Macho>(); // test CC mechanics
        objManager.PushObject(gameObject);
        levelManager.AddObject(gameObject);

    }

    // Goal
    {
        //gameObject = new GameObject();
        //manager->AddEntity(gameObject);
        //gameObject->GetComponent<Transform>().position = Vector2D_float(((30 * _tileSize) + _midPointX) * RATIO, ((8 * _tileSize) + _midPointY) * RATIO);
        //gameObject->GetComponent<Transform>().scale = Vector2D_float(0.1 * 16 * RATIO, 4 * 16 * RATIO);
        //gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 0.0f, &camera, false);
        //gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::GOAL_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
        //    true /* overlap */, false /* movable */, "BENNY_ANIM_MESH" /* any mesh is fine as long as 1:1 */, &camera);

        //objManager.PushObject(gameObject);
        //levelManager.SetGoal(*gameObject);

        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(((29 * _tileSize) + _midPointX) * RATIO, ((6 * _tileSize) + _midPointY) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(2 * 16 * RATIO, 2 * 16 * RATIO);
        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "2x2_MESH", "LEVEL_ASSET_TEX", 0.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(11, 2);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::GOAL_COLLISION, gameObject->GetComponent<Transform>().scale.x/4, gameObject->GetComponent<Transform>().scale.y*2,
           true /* overlap */, false /* movable */, "BENNY_ANIM_MESH" /* any mesh is fine as long as 1:1 */, &camera);
        gameObject->GetComponent<BoxCollider2D>().SetOffset(1 * 16 * RATIO, 1 * 16 * RATIO);
        gameObject->AddComponent<Goal>(11,4);

        objManager.PushObject(gameObject);
        levelManager.SetGoal(*gameObject);
    }

    levelManager.SetUpCC();
    

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


#pragma endregion
    
    if (audioController.Find("Menu")->isPlayed == true) 
    {
        audioController.Stop();
        audioController.Find("Menu")->isPlayed = false;
    }

    audioController.Play("BGM");
    audioController.Find("BGM")->isPlayed = true;

    //progress = 1;

}
void TestingScene::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    gui_arr.Clear();
}
void TestingScene::Draw()
{
    manager->Draw();
    gui_arr.OnDraw();
}
void TestingScene::Update()
{
    manager->Update();
    levelManager.CheckGoal();
    levelManager.AbilityControl();
    gui_arr.OnUpdate();
    
}
