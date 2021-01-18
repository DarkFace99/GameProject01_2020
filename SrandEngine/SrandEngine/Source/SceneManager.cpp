#include "SceneManager.h"

#include "Source/Input.h"

#include "Entity/Button.h"
#include "Entity/Door.h"
#include "Entity/Elevator.h"
#include "Entity/NPC.h"

#define RATIO SCREEN_WIDTH / 480.0f

namespace Srand 
{
    Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);

    GameObject* gameObject;

    GameObject* button1;
    GameObject* button2;
    GameObject* button3;

    GameObject* benny;
    GameObject* macho;

    std::vector<glm::vec4> tile_info;

	SceneManager* SceneManager::s_instance = nullptr;

	SceneManager::SceneManager() 
	{
		
	}

	void SceneManager::Init()
	{
        manager = &EntityManager::get();

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
                if (i > 5 && i < 29) { tile_info.push_back(glm::vec4(8 + (i * 16), 8, 2, 6)); }
                else { tile_info.push_back(glm::vec4(8 + (i * 16), 8, 2, 5)); }

            }
            /* Second Row */
            for (int i = 0; i < 7; i++)
            {
                if (i > 5) { tile_info.push_back(glm::vec4(8 + (29 * 16), 24, 1, 5)); }
                else if (i == 5) { tile_info.push_back(glm::vec4(8 + (i * 16), 24, 3, 5)); }
                else { tile_info.push_back(glm::vec4(8 + (i * 16), 24, 2, 5)); }
            }
            /* Third Row */
            for (int i = 0; i < 7; i++)
            {
                if (i > 5) { tile_info.push_back(glm::vec4(8 + (29 * 16), 40, 1, 5)); }
                else if (i == 5) { tile_info.push_back(glm::vec4(8 + (i * 16), 40, 3, 6)); }
                else { tile_info.push_back(glm::vec4(8 + (i * 16), 40, 2, 6)); }
            }
            /* Forth Row */
            tile_info.push_back(glm::vec4(8 + (29 * 16), 56, 1, 5));
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

            objManager.push_back(gameObject);
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
            objManager.push_back(gameObject);

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
            objManager.push_back(gameObject);

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
            objManager.push_back(gameObject);
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

            objManager.push_back(gameObject);

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

            objManager.push_back(gameObject);
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

            objManager.push_back(gameObject);

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

            objManager.push_back(gameObject);
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

        /* Character */

        // NPC
        {
            gameObject = new GameObject();
            manager->AddEntity(gameObject);
            gameObject->GetComponent<Transform>().position = Vector2D_float(-122.0f, 130.0f);
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

            npc = gameObject;
            objManager.push_back(gameObject);
        }

        // Benny
        {
            gameObject = new GameObject();
            manager->AddEntity(gameObject);
            gameObject->GetComponent<Transform>().position = Vector2D_float(-555.0f, -200.0f);
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

            player = gameObject; // check collision
            benny = player;

            objManager.push_back(gameObject);

            Input::get().AddCharacterList("Benny", benny);
            Input::get().SetControl("Benny");
        }

        // Macho
        {
            gameObject = new GameObject();
            manager->AddEntity(gameObject);
            gameObject->GetComponent<Transform>().position = Vector2D_float(60.0f, -285.0f);
            gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
            gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::CHARACTER_LAYER, "MACHO_ANIM_MESH", "MACHO_ANIM_TEX", 1.0f, &camera, true);
            gameObject->AddComponent<RigidBody>(8.0f);

            gameObject->AddComponent<Animator>(20, 100);
            gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 4);
            gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 13, 19);
            gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x - 20, gameObject->GetComponent<Transform>().scale.y,
                false /* overlap */, true /* movable *//*, "BENNY_ANIM_MESH", &camera*/);

            macho = gameObject;
            objManager.push_back(gameObject);
            Input::get().AddCharacterList("Macho", macho);
        }

#pragma endregion
	}
	void SceneManager::Clean()
	{
		
	}

	void SceneManager::Draw()
	{
		manager->Draw();
	}
	void SceneManager::Update()
	{
		manager->Update();

		// Check Collision
		for (int i = 0; i < objManager.size(); i++)
		{
			if (objManager[i]->GetComponent<BoxCollider2D>().GetTag() != BoxCollider2D::TILE_COLLISION) {
				bool isGroundCheck = false;
				for (int j = 0; j < objManager.size(); j++)
				{
					if (i == j) { break; } // Always Collide with itself

					if (Collision::AABB(objManager[i]->GetComponent<BoxCollider2D>(), objManager[j]->GetComponent<BoxCollider2D>())
						&& objManager[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION)
					{
						if (Collision::IsOnGround(*objManager[i], *objManager[j])) {
							isGroundCheck = true;

							objManager[i]->GetComponent<BoxCollider2D>().SetIsGround(true);
							objManager[i]->GetComponent<RigidBody>().SetVelocityY(0.0f);
						}
					}
				}
				if (isGroundCheck == false) { objManager[i]->GetComponent<BoxCollider2D>().SetIsGround(false); }
			}
		}
	}

	void SceneManager::SceneCheck()
	{

	}
}