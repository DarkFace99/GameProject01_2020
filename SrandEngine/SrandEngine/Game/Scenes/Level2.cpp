#include "Level2.h"

#include "Source/Camera.h"

#include "Entity/Button.h"
#include "Entity/Door.h"
#include "Entity/Elevator.h"
#include "Entity/NPC.h"
#include "Entity/Benny.h"
#include "Entity/Macho.h"
#include "Entity/Cherry.h"
#include "Entity/Pear.h"
#include "Entity/Barter.h"

#include "Source/Audio.h"

Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);
ObjManager& objManager = ObjManager::get();
LevelManager& levelManager = LevelManager::get();
GameObject* gameObject;

AudioController& audioController = AudioController::get();

//GameObject* npc;
//GameObject* player;
//GameObject* benny;
//GameObject* macho;

GameObject* button1;
GameObject* button2;
GameObject* button3;

Level2::Level2()
	:Scene("Level2")
{}

Level2::~Level2()
{
}

void Level2::Init()
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
            if (i == 16) { tile_info.push_back(glm::vec4(8 + (i * 16), 8, 2, 5)); } //inner Dirt
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 8, 2, 6)); } //grass top

        }
        /* Second Row */
        tile_info.push_back(glm::vec4(8 + (16 * 16), 24, 2, 5)); //inner Dirt
        /* Third Row */
        tile_info.push_back(glm::vec4(8 + (16 * 16), 40, 2, 5)); //inner Dirt
        /* Forth Row */
        tile_info.push_back(glm::vec4(8 + (16 * 16), 56, 2, 5)); //inner Dirt
        /* Fifth Row */
        for (int i = 8; i < 14; i++)
        {
            if (i == 8) { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 1, 2)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 2, 2)); }
        }
        for (int i = 18; i < 30; i++)
        {
            if (i == 29) { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 2, 6)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 2, 2)); }
        }
        /* Tenth Row */
        for (int i = 15; i < 24; i++)
        {
            if (i == 23) { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 3, 2)); }
            else if (i == 15) { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 1, 4)); }
            else if (i == 16) { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 2, 4)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 2, 2)); }
        }
        /* Eleventh Row */
        for (int i = 9; i < 17; i++)
        {
            if (i == 9) { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 1, 4)); }
            else if (i == 15) { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 2, 6)); }
            else if (i == 16) { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 3, 6)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 2, 2)); }
        }
        /* Remaining Row */
        for (int i = 1; i < 6; i++)
        {
            if (i < 5) { tile_info.push_back(glm::vec4(152, 164 + (i * 16), 6, 5)); }
            else { tile_info.push_back(glm::vec4(152, 164 + (i * 16), 6, 6)); }
        }
    }

    for (int i = 0; i < tile_info.size(); i++)
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + tile_info[i].x) * RATIO, (-135.0f + tile_info[i].y) * RATIO);
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
}

void Level2::Clean()
{
}

void Level2::Draw()
{
}

void Level2::Update()
{
}
