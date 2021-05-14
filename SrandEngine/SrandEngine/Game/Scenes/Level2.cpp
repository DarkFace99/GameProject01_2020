#include "Level2.h"

Level2::Level2()
	:Scene("Level2")
{}

Level2::~Level2()
{
    Clean();
}

void Level2::Init()
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
            if (i == 16) {  tile_info.push_back(glm::vec4(i, 0, 2, 5)); } //inner Dirt
            else {          tile_info.push_back(glm::vec4(i, 0, 2, 6)); } //grass top

        }
        /* Second Row */
        tile_info.push_back(glm::vec4(16, 1, 2, 5)); //inner Dirt
        /* Third Row */
        tile_info.push_back(glm::vec4(16, 2, 2, 5)); //inner Dirt
        /* Forth Row */
        for (int i = 11; i < 21; i++)
        {
            if (i == 16) {  tile_info.push_back(glm::vec4(i, 3, 2, 5)); }
            else {          tile_info.push_back(glm::vec4(i, 3, 2, 2)); }
        }
        /* Seventh Row */
        for (int i = 0; i < 30; i++)
        {
            if (i >= 0 && i <= 10) {        tile_info.push_back(glm::vec4(i, 6, 2, 2)); }
            else if (i == 11) {             tile_info.push_back(glm::vec4(i, 6, 3, 2)); }
            else if (i == 21) {             tile_info.push_back(glm::vec4(i, 6, 1, 2)); }
            else if (i > 21 && i < 30) {    tile_info.push_back(glm::vec4(i, 6, 2, 2)); }
        }

        /* Remaining Row */
        for (int i = 8; i < 16; i++) 
        {
            if (i == 8) { tile_info.push_back(glm::vec4(16, i, 6, 4)); }
            else if (i == 15) { tile_info.push_back(glm::vec4(16, i, 6, 6)); }
            else { tile_info.push_back(glm::vec4(16, i, 6, 5)); }
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + (27 * 16)) * RATIO, (_midPointY + _offset + (7 * _tileSize)) * RATIO);
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

    }

    // DOOR_STAND
    {
        // 1
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (16 * 16)) * RATIO, (_midPointY + _offset + (3 * _tileSize)) * RATIO);
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

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + 8 + (16 * 16)) * RATIO, (_midPointY + _offset + (5.5 * _tileSize)) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 64.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::ASSET_LAYER, "DOOR_MESH", "LEVEL_ASSET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(14, 14);
        gameObject->GetComponent<TileSelector>().SetTile(1, 9);

        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::ASSET_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
            false, false/*, "DOOR_MESH", &camera*/);
        gameObject->AddComponent<Door>();
        gameObject->GetComponent<Door>().AddConnectedButtons(button1);

        objManager.PushObject(gameObject);

    }


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

    // Cherry
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        gameObject->GetComponent<Transform>().position = Vector2D_float(-555.0f, 0.0f);
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
        gameObject->GetComponent<Transform>().position = Vector2D_float(140.0f, -270.0f);
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

#pragma region GUI

    // selector

    tempgui = new GameObject();
    //tempgui->GetComponent<Transform>().position = Vector2D_float(((6.5 * _tileSize) + _midPointX) * RATIO, (((13.95 - (i * 3)) * _tileSize) + _midPointY) * RATIO);
    tempgui->GetComponent<Transform>().scale = Vector2D_float(16 * RATIO, 16 * RATIO);

    tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "SELECTOR_MESH", "SELECTOR_TEX", 1.0f, &camera, false);
    tempgui->AddComponent<Animator>(3, 100);
    tempgui->GetComponent<Animator>().SetState("WHITE", 2, 2);
    tempgui->GetComponent<Animator>().SetState("YELLOW", 1, 1);
    tempgui->GetComponent<Animator>().SetState("RED", 0, 0);

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

    //progress = 2;
}

void Level2::Clean()
{
    manager->Clean();
    objManager.Clean();
    levelManager.Clean();
    gui_arr.Clear();
}
void Level2::Draw()
{
    manager->Draw();
    gui_arr.OnDraw();
}
void Level2::Update()
{
    manager->Update();
    levelManager.CheckGoal();
    levelManager.AbilityControl();
    gui_arr.OnUpdate();

}
