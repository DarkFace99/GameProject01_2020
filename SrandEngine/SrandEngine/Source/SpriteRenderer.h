#pragma once

/* Custom Header */
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "AssetManager.h"

class SpriteRenderer : public Component {
private:
	bool flip = false;

	Transform* transform;
	std::string textureID = "";
	std::string meshID = "";

	Texture* texture;
	Mesh* mesh;
	
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;

	SpriteRenderer(std::string meshID, std::string textureID) : meshID(meshID), textureID(textureID) {}

	bool Init() override final {
		transform = &gameObject->GetComponent<Transform>();
		texture = AssetManager::get().LoadTexture(textureID);
		mesh = AssetManager::get().LoadMesh(meshID);
	}

	void Draw() override final {
		
	}

	void Update() override final {
	
	}

};